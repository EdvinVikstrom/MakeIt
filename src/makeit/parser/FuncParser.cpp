#include "makeit/parser/Parser.hpp"

int makeit::Parser::parse_function(const Token* &iter)
{
  const Token* function_token = iter++;

  /* Must be atleast 1 argument */
  me::vector<Variable*> call_args;

  while (iter->type != TOKEN_TYPE_END)
  {
    /* Get next argument / variable */
    Variable* arg_variable;
    parse_value(iter, arg_variable);
    call_args.push_back(arg_variable);

    /* If the next token is a ',' then add more arguments */
    if (iter->type == TOKEN_TYPE_PUNCTUATOR && iter->location.pos == ",")
      iter++;
    else
      break;
    }

  /* Get the function to call */
  Function* function = context.functions.at(function_token->location.pos, nullptr);

  /* Check if the function was not found */
  if (function == nullptr)
  {
    char temp[function_token->location.pos.size() + 1];
    throw LocException(function_token->location,
        "undefined function '%s'", function_token->location.pos.c_str(temp));
  }

  /* Check if required argument count matched */
  if (function->args.size() != call_args.size())
  {
    throw LocException(function_token->location,
	"expected %lu argument(s) but %lu was provided", function->args.size(), call_args.size());
  }

  for (me::size_t i = 0; i < function->args.size(); i++)
  {
    try {
      function->args.at(i)->validate(call_args.at(i), logger);
    }catch (const RuntimeException &e)
    {
      char temp[function_token->location.pos.size() + 1];
      logger.trace(function_token->location,
	  "from function '%s' at argument %lu", function_token->location.pos.c_str(temp), i);
      throw;
    }
  }

  /* Calling the function */
  try {
    function->func(call_args, context, context.func_user_ptr);
  }catch (const RuntimeException &e)
  {
    char temp[function_token->location.pos.size() + 1];
    throw LocException(function_token->location,
        "in function '%s': %s", function_token->location.pos.c_str(temp), e.get_message());
  }



  return 0;
}
