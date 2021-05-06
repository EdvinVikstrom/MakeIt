#include "makeit/functions/FnInstall.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

int makeit::func_install_init(Context &context)
{
  Function* function = new Function{
    {
      new StringArg(),
      new StringArg()
    }, func_install};
  context.functions.put("install", function);
  return 0;
}

int makeit::func_install(const me::vector<Variable*> &args, Context &context, void* ptr)
{
  ProjectVar &project = *reinterpret_cast<ProjectVar*>(context.variables.at(ProjectVar::VARIABLE_NAME));

  const StringVar* src_string = reinterpret_cast<const StringVar*>(args.at(0));
  const StringVar* dest_string = reinterpret_cast<const StringVar*>(args.at(1));

  project.installs.emplace_back(src_string->value, dest_string->value);
  return 0;
}
