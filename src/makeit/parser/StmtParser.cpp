#include "makeit/parser/Parser.hpp"

int makeit::Parser::parse_statement(const Token* &iter)
{
  const Token* statement_token = iter++;

  if (statement_token->location.pos == "if")
  {
    bool value = false;
    parse_statement_condition(iter, value);

    const Token* then_token = iter++;
    if (then_token->type != TOKEN_TYPE_STATEMENT || then_token->location.pos != "then")
    {
      throw LocException(statement_token->location,
	  "expected 'then' after if statement condition");
    }

    bool end_found = false;

    /* Executing everything inside if statement */
    if (value)
      execute_statement_body(iter, end_found);

    /* Skipping everything inside if statement */
    else
      skip_statement_body(iter, end_found);

    if (!end_found)
    {
      throw LocException(statement_token->location,
	  "no end point found");
    }

  /* For loop */
  }else if (statement_token->location.pos == "for")
  {
  }else
  {
    char temp[statement_token->location.pos.size() + 1];
    throw LocException(statement_token->location,
	"unknown statement '%s'", statement_token->location.pos.c_str(temp));
  }

  return 0;
}

int makeit::Parser::parse_statement_condition(const Token* &iter, bool &value)
{
  Variable* accumulator;
  parse_expression(iter, accumulator, value);

  if (iter->type == TOKEN_TYPE_STATEMENT)
  {
    if (iter->location.pos == "and")
    {
      iter++;
      bool value2 = false;
      parse_statement_condition(iter, value2);
      value = value && value2;
    }else if (iter->location.pos == "or")
    {
      iter++;
      bool value2 = false;
      parse_statement_condition(iter, value2);
      value = value || value2;
    }
  }
  return 0;
}

int makeit::Parser::skip_statement_body(const Token* &iter, bool &end_found)
{
  size_t scope_index = 1;
  while (iter->type != TOKEN_TYPE_END)
  {
    if (iter->type == TOKEN_TYPE_STATEMENT)
    {
      if (iter->location.pos == "end")
      {
      	iter++;
      	scope_index--;
	end_found = true;
	if (scope_index == 0)
	  break;
      }else if (iter->location.pos == "then")
      {
      	iter++;
      	scope_index++;
      }
    }

    iter++;
  }
  return 0;
}

int makeit::Parser::execute_statement_body(const Token* &iter, bool &end_found)
{
  while (iter->type != TOKEN_TYPE_END)
  {
    /* Check if 'end' operator is reached */
    if (iter->type == TOKEN_TYPE_STATEMENT && iter->location.pos == "end")
    {
      iter++;
      end_found = true;
      break;
    }

    parse_token(iter);
  }
  return 0;
}
