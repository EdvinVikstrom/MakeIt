#include "makeit/parser/Parser.hpp"

makeit::Parser::Parser(Logger &logger, me::allocator &alloc, Context &context)
  : logger(logger), alloc(alloc), context(context)
{
}

int makeit::Parser::parse(const Token* tokens)
{
  const Token* iter = tokens;

  while (iter->type != TOKEN_TYPE_END)
  {
    parse_token(iter);
  }
  return 0;
}

int makeit::Parser::parse_token(const Token* &iter)
{
  /* Statement (if / elif / for ...) */
  if (iter->type == TOKEN_TYPE_STATEMENT)
  {
    return parse_statement(iter);

  /* Function call */
  }else if (iter->type == TOKEN_TYPE_FUNCTION)
  {
    return parse_function(iter);

  /* Comment */
  }else if (iter->type == TOKEN_TYPE_COMMENT)
  {
    iter++;
    return 0;
  }else if (iter->type == TOKEN_TYPE_LITERIAL)
  {
    Variable* accumulator;
    bool result;
    return parse_expression(iter, accumulator, result);

  }

  throw LocException(iter->location,
      "unexpected token '%s'", token_type_name(iter->type));
}

int makeit::Parser::parse_string(me::string &value, const TokenLocation &location)
{
  me::size_t index = 0;
  while (index < value.size())
  {
    me::size_t begin = value.find("$(");

    if (begin == me::string::npos)
      break;

    index += 2; /* skipping $( */

    me::size_t end = value.find(')', index);

    if (end == me::string::npos)
      continue;

    const me::string_view key(value.begin() + index, value.begin() + end);

    if (!context.variables.contains(key))
    {
      char temp[key.size() + 1];
      throw LocException(location, "undefined variable '%s' in string", key.c_str(temp));
    }

    const me::string var_value = context.variables.at(key)->as_string();
    value.replace(value.begin() + begin, value.begin() + end + 1, var_value);

    index += 1; /* skipping ) */
  }
  return 0;
}
