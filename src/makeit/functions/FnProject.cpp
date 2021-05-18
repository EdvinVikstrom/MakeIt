#include "makeit/functions/FnProject.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

namespace makeit {

  static const me::vector<FuncArgument> variant1 = {
    {"config", Variable::TABLE},
  };

}

makeit::ProjectFunc::ProjectFunc()
  : Function("project")
{
  variants.push_back(FuncVariant(1, variant1));
}

int makeit::ProjectFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  const TableVar* project_table = reinterpret_cast<TableVar*>(args.at(0));

  project.name = reinterpret_cast<StringVar*>(project_table->value.at("name"))->value;

  /* Getting the version */
  if (project_table->value.contains("version"))
  {
    Variable* variable = project_table->value.at("version");
    project.version = reinterpret_cast<StringVar*>(variable)->value;
  }else
    project.version = "";

  return 0;
}
