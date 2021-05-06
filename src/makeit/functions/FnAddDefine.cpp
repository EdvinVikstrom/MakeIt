#include "makeit/functions/FnAddDefine.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

int makeit::func_add_define_init(Context &context)
{
  Function* function = new Function{
    {
    }, func_add_define};
  context.functions.put("add_define", function);
  return 0;
}

int makeit::func_add_define(const me::vector<Variable*> &args, Context &context, void* ptr)
{
  ProjectVar &project = *reinterpret_cast<ProjectVar*>(context.variables.at(ProjectVar::VARIABLE_NAME));
  // TODO:

  if (args.size() == 2)
  {
    Variable* name_var = args.at(0);

    Variable* value_var = args.at(1);
  }else
  {
    Variable* name_var = args.at(0);
  }
  return 0;
}
