#include "makeit/functions/FnAddPackage.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

int makeit::func_add_package_init(Context &context)
{
  Function* function = new Function{
    {
    }, func_add_package};
  context.functions.put("add_package", function);
  return 0;
}

/*
 * args[0]: package (STRING)
 * args[1]: cflags (ARRAY)
 * args[2]: lflags (ARRAY)
 */
int makeit::func_add_package(const me::vector<Variable*> &args, Context &context, void* ptr)
{
  ProjectVar &project = *reinterpret_cast<ProjectVar*>(context.variables.at(ProjectVar::VARIABLE_NAME));
  return 0;
}
