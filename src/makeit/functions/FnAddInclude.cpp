#include "makeit/functions/FnAddInclude.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

int makeit::func_add_include_init(Context &context)
{
  Function* function = new Function{
    {
    }, func_add_include};
  context.functions.put("add_include", function);
  return 0;
}

int makeit::func_add_include(const me::vector<Variable*> &args, Context &context, void* ptr)
{
  return 0;
}
