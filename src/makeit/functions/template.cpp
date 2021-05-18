#include "makeit/functions/FnNameHere.hpp"

namespace makeit {

  static const me::vector<FuncArgument> variant1 = {
  };

}

makeit::NameHereFunc::NameHereFunc()
  : Function("prefix_here")
{
  variants.push_back(FuncVariant(1, variant1));
}

int makeit::NameHereFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  return 0;
}
