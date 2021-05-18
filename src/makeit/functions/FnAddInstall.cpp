#include "makeit/functions/FnAddInstall.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

namespace makeit {

  static const me::vector<FuncArgument> variant1 = {
    {"src", Variable::STRING},
    {"dest", Variable::STRING}
  };

}

makeit::AddInstallFunc::AddInstallFunc()
  : Function("add_install")
{
  variants.push_back(FuncVariant(1, variant1));
}

int makeit::AddInstallFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  const StringVar* src_string = reinterpret_cast<const StringVar*>(args.at(0));
  const StringVar* dest_string = reinterpret_cast<const StringVar*>(args.at(1));

  project.installations.emplace_back(src_string->value, dest_string->value);
  return 0;
}
