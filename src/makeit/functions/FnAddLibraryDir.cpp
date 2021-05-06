#include "makeit/functions/FnAddLibraryDir.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

int makeit::func_add_library_directory_init(Context &context)
{
  Function* function = new Function{
    {
      new ArrayArg(new StringArg())
    }, func_add_library_directory};
  context.functions.put("add_library_directory", function);
  return 0;
}

int makeit::func_add_library_directory(const me::vector<Variable*> &args, Context &context, void* ptr)
{
  ProjectVar &project = *reinterpret_cast<ProjectVar*>(context.variables.at(ProjectVar::VARIABLE_NAME));

  const ArrayVar* directory_array = reinterpret_cast<ArrayVar*>(args.at(0));

  project.library_directories.reserve(project.include_directories.size() + directory_array->value.size());

  for (me::size_t i = 0; i < directory_array->value.size(); i++)
  {
    StringVar* directory_var = reinterpret_cast<StringVar*>(directory_array->value.at(i));
    project.library_directories.push_back(directory_var->value);
  }
  return 0;
}
