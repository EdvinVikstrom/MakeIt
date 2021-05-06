#include "makeit/functions/FnPrint.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

int makeit::func_print_init(Context &context)
{
  Function* function = new Function{
    {
      new StringArg(),
    }, func_print};
  context.functions.put("print", function);
  return 0;
}

int makeit::func_print(const me::vector<Variable*> &args, Context &context, void* ptr)
{
  printf("%s\n", reinterpret_cast<StringVar*>(args.at(0))->value.c_str());
  return 0;
}
