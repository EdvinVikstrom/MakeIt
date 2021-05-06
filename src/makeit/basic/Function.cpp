#include "makeit/basic/Function.hpp"

int makeit::ArgConfig::validate(const Variable* var, Logger &logger) const
{
  if (var->type != type)
  {
    throw RuntimeException("expected type %s but found type %s",
	variable_type_name(type), variable_type_name(var->type));
  }

  switch (type)
  {
    case Variable::TEXT:
      return reinterpret_cast<const TextArg*>(this)->validate(reinterpret_cast<const TextVar*>(var), logger);
    case Variable::STRING:
      return reinterpret_cast<const StringArg*>(this)->validate(reinterpret_cast<const StringVar*>(var), logger);
    case Variable::INTEGER:
      return reinterpret_cast<const IntegerArg*>(this)->validate(reinterpret_cast<const IntegerVar*>(var), logger);
    case Variable::DECIMAL:
      return reinterpret_cast<const DecimalArg*>(this)->validate(reinterpret_cast<const DecimalVar*>(var), logger);
    case Variable::ARRAY:
      return reinterpret_cast<const ArrayArg*>(this)->validate(reinterpret_cast<const ArrayVar*>(var), logger);
    case Variable::TABLE:
      return reinterpret_cast<const TableArg*>(this)->validate(reinterpret_cast<const TableVar*>(var), logger);
    case Variable::TEMP:
    default:
      /* TODO: error */
      break;
  }
  return 0;
}

int makeit::TextArg::validate(const TextVar* var, Logger &logger) const
{
  if (valid.size())
  {
    if (!valid.contains(var->value))
    {
      char temp[var->value.size() + 1];
      throw RuntimeException("'%s' is not a valid value", var->value.c_str(temp));
    }
  }
  return 0;
}

int makeit::StringArg::validate(const StringVar* var, Logger &logger) const
{
  if (var->value.size() < min_len)
      throw RuntimeException("length of string is out of bounds (\e[31m%lu\e[0m < %lu)", var->value.size(), min_len);
  else if (var->value.size() > max_len)
      throw RuntimeException("length of string is out of bounds (\e[31m%lu\e[0m > %lu)", var->value.size(), max_len);
  return 0;
}

int makeit::IntegerArg::validate(const IntegerVar* var, Logger &logger) const
{
  if (var->value < min_num)
      throw RuntimeException("value out of bounds (\e[31m%lu\e[0m < %lu)", var->value, min_num);
  else if (var->value > max_num)
      throw RuntimeException("value out of bounds (\e[31m%lu\e[0m > %lu)", var->value, max_num);
  return 0;
}

int makeit::DecimalArg::validate(const DecimalVar* var, Logger &logger) const
{
  if (var->value < min_num)
      throw RuntimeException("value out of bounds (\e[31m%lu\e[0m < %lu)", var->value, min_num);
  else if (var->value > max_num)
      throw RuntimeException("value out of bounds (\e[31m%lu\e[0m > %lu)", var->value, max_num);
  return 0;
}

int makeit::ArrayArg::validate(const ArrayVar* var, Logger &logger) const
{
  for (me::size_t i = 0; i < var->value.size(); i++)
  {
    try {
      element_config->validate(var->value.at(i), logger);
    }catch (const RuntimeException &e)
    {
      logger.trace("from array at index %lu", i);
      throw;
    }
  }
  return 0;
}

int makeit::TableArg::validate(const TableVar* var, Logger &logger) const
{
  for (auto const [key, val] : layout)
  {
    if (!var->value.contains(key))
    {
      if (val.required)
      {
	char temp[key.size() + 1];
	throw RuntimeException("required entry('%s') not found", key.c_str(temp));
      }else
	continue;
    }

    try {
      val.config->validate(var->value.at(key), logger);
    }catch (const RuntimeException &e)
    {
      char temp[key.size() + 1];
      logger.trace("from table at element '%s'", key.c_str(temp));
      throw;
    }
  }
  return 0;
}

int makeit::StructArg::validate(const StructVar* var, Logger &logger) const
{
  if (name != var->value)
  {
    char temp[var->value.size() + 1];
    throw RuntimeException("'%s' invalid structure '%s'", var->value.c_str(temp));
  }
  return 0;
}
