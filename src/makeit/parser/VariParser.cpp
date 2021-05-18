#include "makeit/parser/Parser.hpp"

int makeit::Parser::parse_value(const Token* &iter, Variable* &variable)
{
  const Token* token = iter++;

  if (token->type == TOKEN_TYPE_LITERIAL)
  {
    /* Check if a variable with the same name exists */
    if (!context.variables.contains(token->location.pos))
    {
      /* Can only create a variable if the next token is a assign character */
      if (iter->type == TOKEN_TYPE_PUNCTUATOR &&
	  (iter->location.pos == "=" || iter->location.pos == "?="))
      {
	variable = alloc.calloc<TempVar>(token->location.pos);
	context.variables.put(token->location.pos, variable);
      }else
      {
	char temp[token->location.pos.size() + 1];
	throw LocException(token->location,
	    "undefined variable '%s'", token->location.pos.c_str(temp));
      }

    /* Create a new variable with the name */
    }else
    {
      variable = context.variables.at(token->location.pos);
    }

  /* String value */
  }else if (token->type == TOKEN_TYPE_STRING)
  {
    const TokenLocation location = token->location;

    me::string string_value(token->location.pos.begin() + 1, token->location.pos.size() - 2);
    parse_string(string_value, location);
    variable = alloc.calloc<StringVar>(string_value);

  /* Integer value */
  }else if (token->type == TOKEN_TYPE_INTEGER)
  {
    const TokenLocation location = token->location;

    /* Try to convert the string to a integer */
    try {
      int integer_value = token->location.pos.as_int<int>();
      variable = alloc.calloc<IntegerVar>(integer_value);
    }catch (me::exception &e)
    {
      char temp[token->location.pos.size() + 1];
      throw LocException(location,
	  "failed to convert string '%s' to integer", token->location.pos.c_str(temp));
    }

  /* Decimal value */
  }else if (token->type == TOKEN_TYPE_DECIMAL)
  {
    const TokenLocation location = token->location;

    float decimal_value = 0.0F; // TODO
    variable = alloc.calloc<DecimalVar>(decimal_value);

  /* Array / Table value */
  }else if (token->type == TOKEN_TYPE_PUNCTUATOR)
  {
    const TokenLocation* first = &iter->location;

    /* Variable exists operator */
    if (token->location.pos == "?")
    {
      const Token* literial_token = iter++;

      const TokenLocation* last = &literial_token->location;
      const TokenLocation location = TokenLocation::merge(*first, *last);

      if (literial_token->type != TOKEN_TYPE_LITERIAL)
	throw LocException(location,
	    "expected literial token");

      /* Check if the variable exists set variable to a integer(true) */
      if (context.variables.contains(literial_token->location.pos))
	variable = alloc.calloc<IntegerVar>(1);

      /* Else set variable to integer(false) */
      else
	variable = alloc.calloc<IntegerVar>(0);

    /* Array */
    }else if (token->location.pos == "[")
    {
      ArrayVar::Value array_value;
      while (iter->type != TOKEN_TYPE_END)
      {
	/* Array end */
	if (iter->type == TOKEN_TYPE_PUNCTUATOR && iter->location.pos == "]")
	  break;

	/* Get next value in array */
	Variable* entry;
	parse_value(iter, entry);
	array_value.push_back(entry);
      }

      const TokenLocation* last = &iter->location;
      const TokenLocation location = TokenLocation::merge(*first, *last);

      variable = alloc.calloc<ArrayVar>(array_value);

      iter++; /* Skipping the ']' character */

    /* Table */
    }else if (token->location.pos == "{")
    {
      TableVar::Value table_value;
      while (iter->type != TOKEN_TYPE_END)
      {
	/* Table end */
	if (iter->type == TOKEN_TYPE_PUNCTUATOR && iter->location.pos == "}")
	  break;

	/* Get next key in table */
	if (iter->type != TOKEN_TYPE_LITERIAL)
	  throw LocException(TokenLocation::merge(*first, iter->location),
	      "expected literial token but found '%s'", token_type_name(iter->type));
	const me::string_view &key = iter++->location.pos;

	/* Get next value in table */
	Variable* value;
	parse_value(iter, value);

	table_value[key] = value;
      }

      const TokenLocation* last = &iter->location;
      const TokenLocation location = TokenLocation::merge(*first, *last);

      variable = alloc.calloc<TableVar>(table_value);

      iter++; /* Skipping the '}' character */

    /* Error */
    }else
    {
      char temp[token->location.pos.size() + 1];
      throw LocException(token->location,
	  "unknown symbol '%s'", token->location.pos.c_str(temp));
    }

  /* Error */
  }else
  {
    throw LocException(iter->location,
	"expected value but found '%s'", token_type_name(iter->type));
  }
  return 0;
}
