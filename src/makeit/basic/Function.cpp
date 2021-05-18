#include "makeit/basic/Function.hpp"

/* ----------------- */
/* class FuncVariant */
/* ----------------- */
makeit::FuncVariant::FuncVariant(me::uint32_t index, const me::vector<FuncArgument> &args)
  : index(index), args(args)
{
}

bool makeit::FuncVariant::validate_args(const me::vector<Variable*> &variables) const
{
  if (variables.size() != args.size())
    return false;

  for (me::size_t i = 0; i != args.size(); i++)
  {
    if (args.at(i).type != variables.at(i)->type)
      return false;
  }
  return true;
}
/* end class FuncVariant */

/* -------------- */
/* class Function */
/* -------------- */
makeit::Function::Function(const me::string_view &name)
  : name(name)
{
}

const makeit::FuncVariant* makeit::Function::match_variant(const me::vector<Variable*> &variables) const
{
  for (const FuncVariant &variant : variants)
  {
    if (variant.validate_args(variables))
      return &variant;
  }
  return nullptr;
}

const me::string_view& makeit::Function::get_name() const
{
  return name;
}

const me::vector<makeit::FuncVariant>& makeit::Function::get_variants() const
{
  return variants;
}
/* end class Function */

/* ---------------- */
/* static functions */
/* ---------------- */
void makeit::write_args_to_string(const me::vector<FuncArgument> &arguments, me::string &string)
{
  string.reserve(128);
  if (arguments.size() != 0)
  {
    string.append(variable_type_name(arguments.at(0).type)).append(' ').append(arguments.at(0).name);
    for (me::size_t i = 1; i != arguments.size(); i++)
      string.append(", ").append(variable_type_name(arguments.at(i).type)).append(' ').append(arguments.at(i).name);
  }
}

void makeit::write_vars_to_string(const me::vector<Variable*> &variables, me::string &string)
{
  string.reserve(128);
  if (variables.size() != 0)
  {
    string.append(variable_type_name(variables.at(0)->type));
    for (me::size_t i = 1; i != variables.size(); i++)
      string.append(", ").append(variable_type_name(variables.at(i)->type));
  }
}
