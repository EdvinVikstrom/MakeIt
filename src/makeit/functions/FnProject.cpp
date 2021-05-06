#include "makeit/functions/FnProject.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

int makeit::func_project_init(Context &context)
{
  Function* function = new Function{
    {
      new TableArg({
	  {"name", {new StringArg(), true}},
	  {"output", {new StringArg({}), true}},

	  {"kind", {new TextArg(get_valid_kind_string()), false}},
	  {"lang", {new TextArg(get_valid_lang_string()), false}},
	  {"cc", {new TextArg(get_valid_cc_string()), false}},
	  {"version", {new StringArg(), false}},
	  {"build", {new StringArg({}), false}}
	  }),
    }, func_project};
  context.functions.put("project", function);
  return 0;
}

int makeit::func_project(const me::vector<Variable*> &args, Context &context, void* ptr)
{
  ProjectVar &project = *reinterpret_cast<ProjectVar*>(context.variables.at(ProjectVar::VARIABLE_NAME));

  const TableVar* project_table = reinterpret_cast<TableVar*>(args.at(0));

  project.name = reinterpret_cast<StringVar*>(project_table->value.at("name"))->value;
  project.output = reinterpret_cast<StringVar*>(project_table->value.at("output"))->value;

  /* Getting the version */
  if (project_table->value.contains("version"))
  {
    Variable* variable = project_table->value.at("version");
    project.version = reinterpret_cast<StringVar*>(variable)->value;
  }else
    project.version = ProjectVar::DEFAULT_VERSION;

  /* Getting the build directory */
  if (project_table->value.contains("build"))
  {
    Variable* variable = project_table->value.at("build");
    project.build = reinterpret_cast<StringVar*>(variable)->value;
  }else
    project.build = ProjectVar::DEFAULT_BUILD_DIR;

  /* Getting the language */
  if (project_table->value.contains("lang"))
  {
    Variable* variable = project_table->value.at("lang");
    const TextVar::Value &text = reinterpret_cast<TextVar*>(variable)->value;
    project.lang = lang_from_string(text);
  }else
    project.lang = ProjectVar::DEFAULT_LANG;

  /* Getting the kind */
  if (project_table->value.contains("kind"))
  {
    Variable* variable = project_table->value.at("kind");
    const TextVar::Value &text = reinterpret_cast<TextVar*>(variable)->value;
    project.kind = kind_from_string(text);
  }else
    project.kind = ProjectVar::DEFAULT_KIND;

  /* Getting the compiler collection */
  if (project_table->value.contains("cc"))
  {
    Variable* variable = project_table->value.at("cc");
    const TextVar::Value &text = reinterpret_cast<TextVar*>(variable)->value;
    project.cc = cc_from_string(text);
  }else
    project.cc = ProjectVar::DEFAULT_CC;
 
  return 0;
}
