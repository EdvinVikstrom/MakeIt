#include "makeit/functions/FnAddExtern.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

namespace makeit {

  static const me::vector<FuncArgument> variant1 = {
    {"command", Variable::STRING},
    {"output", Variable::STRING},
    {"options", Variable::ARRAY}
  };

}

makeit::AddExternFunc::AddExternFunc()
  : Function("add_extern")
{
  variants.push_back(FuncVariant(1, variant1));
}

int makeit::AddExternFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  const StringVar* command_string = reinterpret_cast<const StringVar*>(args.at(0));
  const StringVar* output_string = reinterpret_cast<const StringVar*>(args.at(1));
  const ArrayVar* option_array = reinterpret_cast<const ArrayVar*>(args.at(2));

  External external = {command_string->value, output_string->value};
  external.options.reserve(option_array->value.size());
  for (me::size_t i = 0; i< option_array->value.size(); i++)
  {
    const StringVar* option_var = reinterpret_cast<StringVar*>(option_array->value.at(i));
    external.options.emplace_back(option_var->value);
  }

  project.externals.push_back(external);
  return 0;
}
