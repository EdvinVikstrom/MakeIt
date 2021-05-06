#include "makeit/functions/FnFiles.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

int makeit::func_files_init(Context &context)
{
  /* TODO: multiple variants */
  Function* function = new Function{
    {
      new ArrayArg(new StringArg())
    }, func_files};
  context.functions.put("files", function);
  return 0;
}

int makeit::func_files(const me::vector<Variable*> &args, Context &context, void* ptr)
{
  ProjectVar &project = *reinterpret_cast<ProjectVar*>(context.variables.at(ProjectVar::VARIABLE_NAME));

  const ArrayVar* file_array = reinterpret_cast<const ArrayVar*>(args.at(0));

  project.files.reserve(project.files.size() + file_array->value.size());
  for (me::size_t i = 0; i < file_array->value.size(); i++)
  {
    Variable* var = file_array->value.at(i);

    if (var->type == Variable::STRING)
    {
      const StringVar::Value &file = reinterpret_cast<const StringVar*>(var)->value;

      Lang src_lang;
      if (file.ends_with(".cpp") || file.ends_with(".cxx") || file.ends_with(".cc"))
	src_lang = LANG_CXX;
      else
	src_lang = LANG_C;

      project.files.push_back({reinterpret_cast<StringVar*>(var)->value, {}, src_lang});
    }
  }
  return 0;
}
