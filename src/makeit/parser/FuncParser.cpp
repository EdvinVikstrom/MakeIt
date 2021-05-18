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

  const FuncVariant* func_variant = function->match_variant(call_args);
  if (func_variant == nullptr)
  {
    char temp[function_token->location.pos.size() + 1];
    function_token->location.pos.c_str(temp);

    logger.printf("\nFunction variants:\n");
    for (const FuncVariant &variant : function->get_variants())
    {
      me::string args_string;
      write_args_to_string(variant.args, args_string);
      logger.printf("\n\t%s(%s)\n", temp, args_string.c_str());
    }

    me::string call_args_string;
    write_vars_to_string(call_args, call_args_string);
    throw LocException(function_token->location, "no match for function call %s(%s)",
	temp, call_args_string.c_str());
  }

  /* Calling the function */
  try {
    function->execute(*func_variant, call_args, context);
  }catch (const RuntimeException &e)
  {
    char temp[function_token->location.pos.size() + 1];
    throw LocException(function_token->location,
        "in function '%s': %s", function_token->location.pos.c_str(temp), e.get_message());
  }
  return 0;
}
