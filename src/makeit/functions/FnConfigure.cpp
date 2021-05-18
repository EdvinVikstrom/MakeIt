#include "makeit/functions/FnConfigure.hpp"

namespace makeit {

  static const me::vector<FuncArgument> variant1 = {
  };

}

makeit::ConfigureFunc::ConfigureFunc()
  : Function("configure")
{
  variants.push_back(FuncVariant(1, variant1));
}

int makeit::ConfigureFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  return 0;
}
