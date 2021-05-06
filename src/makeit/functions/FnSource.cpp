#include "makeit/functions/FnSource.hpp"
#include "makeit/MakeIt.hpp"
#include "makeit/Text.hpp"

int makeit::func_source_init(Context &context)
{
  Function* function = new Function{
    {
      new StringArg(),
    }, func_source};
  context.functions.put("source", function);
  return 0;
}

int makeit::func_source(const me::vector<Variable*> &args, Context &context, void* ptr)
{
  Instance* instance = reinterpret_cast<Instance*>(ptr);

  for (me::size_t i = 0; i < args.size(); i++)
  {
    Variable* var = args.at(i);
    instance->read_source(reinterpret_cast<StringVar*>(var)->value);
  }
  return 0;
}
