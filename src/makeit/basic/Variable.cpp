#include "makeit/basic/Variable.hpp"
#include "makeit/Text.hpp"

/* _____________________ */
/* | class TempVar     | */
/* |___________________| */
makeit::TempVar::TempVar(const Value &value)
  : Variable(TEMP), value(value)
{
}

void makeit::TempVar::copy(Variable* &var, me::allocator &alloc) const
{
  throw RuntimeException(Text::Ecannot_copy_type, variable_type_name(TEMP));
}

void makeit::TempVar::assign(Variable* var)
{
  throw RuntimeException(Text::Ecannot_assign_type, variable_type_name(TEMP));
}

void makeit::TempVar::append(Variable* var)
{
  throw RuntimeException(Text::Ecannot_append_type, variable_type_name(TEMP));
}

bool makeit::TempVar::compare(Variable* var) const
{
  throw RuntimeException(Text::Ecannot_compare_type, variable_type_name(TEMP));
}

me::string makeit::TempVar::as_string() const
{
  return "(nil)";
}

/* _____________________ */
/* | class TextVar     | */
/* |___________________| */
makeit::TextVar::TextVar(const Value &value)
  : Variable(TEXT), value(value)
{
}

void makeit::TextVar::copy(Variable* &var, me::allocator &alloc) const
{
  var = alloc.calloc<TextVar>(value);
}

void makeit::TextVar::assign(Variable* var)
{
  if (var->type == TEXT)
    value = reinterpret_cast<TextVar*>(var)->value;
  else
    throw RuntimeException(Text::Ecannot_assign_types, variable_type_name(TEXT), variable_type_name(var->type));
}

void makeit::TextVar::append(Variable* var)
{
  throw RuntimeException(Text::Ecannot_append_type, variable_type_name(TEXT));
}

bool makeit::TextVar::compare(Variable* var) const
{
  if (var->type == TEXT)
    return value == reinterpret_cast<TextVar*>(var)->value;
  else if (var->type == STRING)
    return value == reinterpret_cast<StringVar*>(var)->value;
  throw RuntimeException(Text::Ecannot_compare_types, variable_type_name(TEXT), variable_type_name(var->type));
}

me::string makeit::TextVar::as_string() const
{
  return value;
}

/* _____________________ */
/* | class StringVar   | */
/* |___________________| */
makeit::StringVar::StringVar(const Value &value)
  : Variable(STRING), value(value)
{
}

void makeit::StringVar::copy(Variable* &var, me::allocator &alloc) const
{
  var = alloc.calloc<StringVar>(value);
}

void makeit::StringVar::assign(Variable* var)
{
  if (var->type == STRING)
    value = reinterpret_cast<StringVar*>(var)->value;
  else if (var->type == TEXT)
    value = reinterpret_cast<TextVar*>(var)->value;
  else
    throw RuntimeException(Text::Ecannot_assign_types, variable_type_name(STRING), variable_type_name(var->type));
}

void makeit::StringVar::append(Variable* var)
{
  if (var->type == STRING)
    value += reinterpret_cast<StringVar*>(var)->value;
  else if (var->type == TEXT)
    value += reinterpret_cast<TextVar*>(var)->value;
  else
    throw RuntimeException(Text::Ecannot_append_types, variable_type_name(STRING), variable_type_name(var->type));
}

bool makeit::StringVar::compare(Variable* var) const
{
  if (var->type == STRING)
    return value == reinterpret_cast<StringVar*>(var)->value;
  else if (var->type == TEXT)
    return value == reinterpret_cast<TextVar*>(var)->value;
  throw RuntimeException(Text::Ecannot_compare_types, variable_type_name(STRING), variable_type_name(var->type));
}

me::string makeit::StringVar::as_string() const
{
  return value;
}

/* _____________________ */
/* | class IntegerVar  | */
/* |___________________| */
makeit::IntegerVar::IntegerVar(const Value &value)
  : Variable(INTEGER), value(value)
{
}

void makeit::IntegerVar::copy(Variable* &var, me::allocator &alloc) const
{
  var = alloc.calloc<IntegerVar>(value);
}

void makeit::IntegerVar::assign(Variable* var)
{
  if (var->type == INTEGER)
    value = reinterpret_cast<IntegerVar*>(var)->value;
  else if (var->type == DECIMAL) /* TODO: warning */
    value = reinterpret_cast<DecimalVar*>(var)->value;
  else
    throw RuntimeException(Text::Ecannot_assign_types, variable_type_name(INTEGER), variable_type_name(var->type));
}

void makeit::IntegerVar::append(Variable* var)
{
  if (var->type == INTEGER)
    value += reinterpret_cast<IntegerVar*>(var)->value;
  else if (var->type == DECIMAL) /* TODO: warning */
    value += reinterpret_cast<DecimalVar*>(var)->value;
  else
    throw RuntimeException(Text::Ecannot_append_types, variable_type_name(INTEGER), variable_type_name(var->type));
}

bool makeit::IntegerVar::compare(Variable* var) const
{
  if (var->type == INTEGER)
    return value == reinterpret_cast<IntegerVar*>(var)->value;
  else if (var->type == DECIMAL)
    return value == reinterpret_cast<DecimalVar*>(var)->value;
  throw RuntimeException(Text::Ecannot_compare_types, variable_type_name(INTEGER), variable_type_name(var->type));
}

me::string makeit::IntegerVar::as_string() const
{
  char str[24];
  me::intstr(value, str);
  return str;
}

/* _____________________ */
/* | class DecimalVar  | */
/* |___________________| */
makeit::DecimalVar::DecimalVar(const Value &value)
  : Variable(DECIMAL), value(value)
{
}

void makeit::DecimalVar::copy(Variable* &var, me::allocator &alloc) const
{
  var = alloc.calloc<DecimalVar>(value);
}

void makeit::DecimalVar::assign(Variable* var)
{
  if (var->type == DECIMAL)
    value = reinterpret_cast<DecimalVar*>(var)->value;
  else if (var->type == DECIMAL)
    value = reinterpret_cast<IntegerVar*>(var)->value;
  else
    throw RuntimeException(Text::Ecannot_assign_types, variable_type_name(DECIMAL), variable_type_name(var->type));
}

void makeit::DecimalVar::append(Variable* var)
{
  if (var->type == DECIMAL)
    value += reinterpret_cast<DecimalVar*>(var)->value;
  else if (var->type == INTEGER)
    value += reinterpret_cast<IntegerVar*>(var)->value;
  else
    throw RuntimeException(Text::Ecannot_append_types, variable_type_name(DECIMAL), variable_type_name(var->type));
}

bool makeit::DecimalVar::compare(Variable* var) const
{
  if (var->type == DECIMAL)
    return value == reinterpret_cast<DecimalVar*>(var)->value;
  else if (var->type == INTEGER)
    return value == reinterpret_cast<IntegerVar*>(var)->value;
  throw RuntimeException(Text::Ecannot_compare_types, variable_type_name(DECIMAL), variable_type_name(var->type));
}

me::string makeit::DecimalVar::as_string() const
{
  char str[24];
  me::floatstr(value, str);
  return str;
}

/* _____________________ */
/* | class ArrayVar    | */
/* |___________________| */
makeit::ArrayVar::ArrayVar(const Value &value)
  : Variable(ARRAY), value(value)
{
}

void makeit::ArrayVar::copy(Variable* &var, me::allocator &alloc) const
{
  var = alloc.calloc<ArrayVar>(value);
}

void makeit::ArrayVar::assign(Variable* var)
{
  if (var->type == ARRAY)
    value = reinterpret_cast<ArrayVar*>(var)->value;
  else
    throw RuntimeException(Text::Ecannot_assign_types, variable_type_name(ARRAY), variable_type_name(var->type));
}

void makeit::ArrayVar::append(Variable* var)
{
  if (var->type == Variable::ARRAY)
  {
    ArrayVar* arr_var = reinterpret_cast<ArrayVar*>(var);
    value.reserve(value.size() + arr_var->value.size());
    for (Variable* i : arr_var->value)
      value.push_back(i);
  }else
    value.push_back(var);
}

bool makeit::ArrayVar::compare(Variable* var) const
{
  if (var->type == ARRAY)
    return value == reinterpret_cast<ArrayVar*>(var)->value;
  else if (var->type == INTEGER)
    return value.size() == reinterpret_cast<IntegerVar*>(var)->value;
  else if (var->type == DECIMAL)
    return value.size() == reinterpret_cast<DecimalVar*>(var)->value;
  throw RuntimeException(Text::Ecannot_compare_types, variable_type_name(ARRAY), variable_type_name(var->type));
}

me::string makeit::ArrayVar::as_string() const
{
  char str[64];
  ::sprintf(str, "array[%lu]{...}", value.size());
  return str;
}

/* _____________________ */
/* | class TableVar    | */
/* |___________________| */
makeit::TableVar::TableVar(const Value &value)
  : Variable(TABLE), value(value)
{
}

void makeit::TableVar::copy(Variable* &var, me::allocator &alloc) const
{
  var = alloc.calloc<TableVar>(value);
}

void makeit::TableVar::assign(Variable* var)
{
  throw RuntimeException(Text::Ecannot_assign_type, variable_type_name(TABLE));
}

void makeit::TableVar::append(Variable* var)
{
  throw RuntimeException(Text::Ecannot_append_type, variable_type_name(TABLE));
}

bool makeit::TableVar::compare(Variable* var) const
{
  throw RuntimeException(Text::Ecannot_compare_type, variable_type_name(TABLE));
}

me::string makeit::TableVar::as_string() const
{
  char str[64];
  ::sprintf(str, "table[%lu]{...}", value.size());
  return str;
}

/* _____________________ */
/* | class StructVar   | */
/* |___________________| */
makeit::StructVar::StructVar(const Value &value)
  : Variable(STRUCT), value(value)
{
}

void makeit::StructVar::copy(Variable* &var, me::allocator &alloc) const
{
  throw RuntimeException(Text::Ecannot_copy_type, variable_type_name(STRUCT));
}

void makeit::StructVar::assign(Variable* var)
{
  throw RuntimeException(Text::Ecannot_assign_type, variable_type_name(STRUCT));
}

void makeit::StructVar::append(Variable* var)
{
  throw RuntimeException(Text::Ecannot_append_type, variable_type_name(STRUCT));
}

bool makeit::StructVar::compare(Variable* var) const
{
  throw RuntimeException(Text::Ecannot_compare_type, variable_type_name(STRUCT));
}

me::string makeit::StructVar::as_string() const
{
  return "(nil)";
}

const char* makeit::variable_type_name(Variable::Type type)
{
  switch (type)
  {
    case Variable::TEMP: return "TEMP";
    case Variable::TEXT: return "TEXT";
    case Variable::STRING: return "STRING";
    case Variable::INTEGER: return "INTEGER";
    case Variable::DECIMAL: return "DECIMAL";
    case Variable::ARRAY: return "ARRAY";
    case Variable::TABLE: return "TABLE";
    case Variable::STRUCT: return "STRUCT";
    default: return "?";
  }
}
