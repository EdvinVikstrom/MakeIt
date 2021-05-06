#include "makeit/parser/Parser.hpp"

int makeit::Parser::parse_expression(const Token* &iter, Variable* &accumulator, bool &result)
{
  parse_value(iter, accumulator);

  /* Check if value is equal or something */
  if (iter->type == TOKEN_TYPE_PUNCTUATOR)
  {
    const Token* punctuator_token = iter++;

    Variable* rvalue;
    bool result2 = false;
    parse_expression(iter, rvalue, result2);

    /* Assign variable to another variable */
    if (punctuator_token->location.pos == "=")
    {
      if (accumulator->type == Variable::TEMP)
      {
        const me::string_view var_name = reinterpret_cast<TempVar*>(accumulator)->value;
        alloc.dealloc(accumulator);
        rvalue->copy(accumulator, alloc);
        context.variables.put(var_name, accumulator);

      }else
      {
        /* Try to assign accumulator to value */
        try {
          accumulator->assign(rvalue);
        }catch (const RuntimeException &e)
        {
          throw LocException(punctuator_token->location, e.get_message());
        }
      }

    /* Assign variable if not assigned */
    }else if (punctuator_token->location.pos == "?=")
    {
      if (accumulator->type == Variable::TEMP)
      {
        const me::string_view var_name = reinterpret_cast<TempVar*>(accumulator)->value;
        alloc.dealloc(accumulator);
        rvalue->copy(accumulator, alloc);
        context.variables.put(var_name, accumulator);
      }

    /* Append variable with another variable */
    }else if (punctuator_token->location.pos == "+=")
    {
      /* Try to append accumulator with value */
      try {
        accumulator->append(rvalue);
      }catch (const RuntimeException &e)
      {
        throw LocException(punctuator_token->location, e.get_message());
      }

    /* Compare two variables */
    }else if (punctuator_token->location.pos == "==")
    {
      /* Try to compare accumulator with value */
      try {
        result = accumulator->compare(rvalue);
      }catch (const RuntimeException &e)
      {
        throw LocException(punctuator_token->location, e.get_message());
      }

    }else
    {
      throw LocException(punctuator_token->location,
          "invalid operator");
    }

  }else
  {
    if (accumulator->type == Variable::INTEGER)
      result = reinterpret_cast<IntegerVar*>(accumulator)->value;
  }
  return 0;
}
