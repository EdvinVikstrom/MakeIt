#include "makeit/functions/FnAddLFlags.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

int makeit::func_add_lflags_init(Context &context)
{
  Function* function = new Function{
    {
      new ArrayArg(new StringArg())
    }, func_add_lflags};
  context.functions.put("add_lflags", function);
  return 0;
}

int makeit::func_add_lflags(const me::vector<Variable*> &args, Context &context, void* ptr)
{
  ProjectVar &project = *reinterpret_cast<ProjectVar*>(context.variables.at(ProjectVar::VARIABLE_NAME));

  const ArrayVar* flag_array = reinterpret_cast<const ArrayVar*>(args.at(0));

  project.lflags.reserve(project.lflags.size() + flag_array->value.size());

  for (me::size_t i = 0; i < flag_array->value.size(); i++)
  {
    StringVar* flag_var = reinterpret_cast<StringVar*>(flag_array->value.at(i));
    project.lflags.emplace_back(flag_var->value);
  }
  return 0;
}
