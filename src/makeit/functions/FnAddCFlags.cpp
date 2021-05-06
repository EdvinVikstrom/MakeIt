#include "makeit/functions/FnAddCFlags.hpp"
#include "makeit/basic/Project.hpp"
#include "makeit/Text.hpp"

int makeit::func_add_cflags_init(Context &context)
{
  Function* function = new Function{
    {
      new ArrayArg(new TextArg(get_valid_lang_string())),
      new ArrayArg(new StringArg())
    }, func_add_cflags};
  context.functions.put("add_cflags", function);
  return 0;
}

int makeit::func_add_cflags(const me::vector<Variable*> &args, Context &context, void* ptr)
{
  ProjectVar &project = *reinterpret_cast<ProjectVar*>(context.variables.at(ProjectVar::VARIABLE_NAME));

  const ArrayVar* lang_array = reinterpret_cast<const ArrayVar*>(args.at(0));
  const ArrayVar* flag_array = reinterpret_cast<const ArrayVar*>(args.at(1));

  project.cflags.reserve(project.cflags.size() + flag_array->value.size());

  me::uint8_t langs = 0;

  for (me::size_t i = 0; i < lang_array->value.size(); i++)
  {
    Variable* lang_var = lang_array->value.at(i);
    TextVar* lang_text = reinterpret_cast<TextVar*>(lang_var);

    const Lang lang = lang_from_string(lang_text->value);

    langs |= lang;
  }

  for (me::size_t i = 0; i < flag_array->value.size(); i++)
  {
    Variable* flag_var = flag_array->value.at(i);
    project.cflags.emplace_back(reinterpret_cast<StringVar*>(flag_var)->value, langs);
  }
  return 0;
}
