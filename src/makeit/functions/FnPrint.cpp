#include "makeit/functions/FnPrint.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

namespace makeit {

  static const me::vector<FuncArgument> variant1 = {
    {"text", Variable::STRING}
  };

}

makeit::PrintFunc::PrintFunc()
  : Function("print")
{
  variants.push_back(FuncVariant(1, variant1));
}

int makeit::PrintFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  const StringVar* string = reinterpret_cast<StringVar*>(args.at(0));

  printf("%s\n", string->value.c_str());
  return 0;
}
