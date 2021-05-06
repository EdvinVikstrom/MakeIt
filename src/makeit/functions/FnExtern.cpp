#include "makeit/functions/FnExtern.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

int makeit::func_extern_init(Context &context)
{
  Function* function = new Function{
    {
      new TextArg(get_valid_extern_string()),
      new StringArg(),
      new StringArg(),
      new ArrayArg(new StringArg())
    }, func_extern};
  context.functions.put("extern", function);
  return 0;
}

int makeit::func_extern(const me::vector<Variable*> &args, Context &context, void* ptr)
{
  ProjectVar &project = *reinterpret_cast<ProjectVar*>(context.variables.at(ProjectVar::VARIABLE_NAME));

  const TextVar* type_text = reinterpret_cast<const TextVar*>(args.at(0));
  const StringVar* location_string = reinterpret_cast<const StringVar*>(args.at(1));
  const StringVar* output_string = reinterpret_cast<const StringVar*>(args.at(2));
  const ArrayVar* flag_array = reinterpret_cast<const ArrayVar*>(args.at(3));

  const ExternType type = extern_type_from_string(type_text->value);

  me::vector<me::string_view> flags;
  for (me::size_t i = 0; i< flag_array->value.size(); i++)
  {
    const StringVar* flag = reinterpret_cast<StringVar*>(flag_array->value.at(i));
    flags.push_back(flag->value);
  }

  project.externs.emplace_back(location_string->value, output_string->value, flags, type);
  return 0;
}
