#include "makeit/functions/FnAddLibrary.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

int makeit::func_add_library_init(Context &context)
{
  Function* function = new Function{
    {
      new TextArg(get_valid_library_string()),
      new StringArg()
    }, func_add_library};
  context.functions.put("add_library", function);
  return 0;
}

int makeit::func_add_library(const me::vector<Variable*> &args, Context &context, void* ptr)
{
  ProjectVar &project = *reinterpret_cast<ProjectVar*>(context.variables.at(ProjectVar::VARIABLE_NAME));

  TextVar* type_text = reinterpret_cast<TextVar*>(args.at(0));
  StringVar* name_string = reinterpret_cast<StringVar*>(args.at(1));

  const LibraryType type = library_type_from_string(type_text->value);

  project.libraries.emplace_back(name_string->value, type);
  return 0;
}
