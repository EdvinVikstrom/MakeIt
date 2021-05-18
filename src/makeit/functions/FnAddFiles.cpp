#include "makeit/functions/FnAddFiles.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

namespace makeit {

  static const me::vector<FuncArgument> variant1 = {
    {"files", Variable::ARRAY}
  };

}

makeit::AddFilesFunc::AddFilesFunc()
  : Function("add_files")
{
  variants.push_back(FuncVariant(1, variant1));
}

int makeit::AddFilesFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  const ArrayVar* file_array = reinterpret_cast<const ArrayVar*>(args.at(0));

  project.sources.reserve(project.sources.size() + file_array->value.size());
  for (me::size_t i = 0; i < file_array->value.size(); i++)
  {
    const Variable* var = file_array->value.at(i);

    if (var->type == Variable::STRING)
    {
      const StringVar::Value &file = reinterpret_cast<const StringVar*>(var)->value;
      project.sources.emplace_back(file);
    }
  }
  return 0;
}
