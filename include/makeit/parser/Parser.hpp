#ifndef MAKEIT_PARSER_HPP
  #define MAKEIT_PARSER_HPP

#include "makeit/Logger.hpp"
#include "makeit/lexer/Token.hpp"
#include "Context.hpp"

namespace makeit {

  class Parser {

  protected:

    Logger &logger;
    me::allocator &alloc;
    Context &context;

  public:

    Parser(Logger &logger, me::allocator &alloc, Context &context);

    int parse(const Token* tokens);

    int parse_token(const Token* &iter);

    int parse_literial(const Token* &iter);

    int parse_statement(const Token* &iter);
    int parse_statement_condition(const Token* &iter, bool &value);
    int skip_statement_body(const Token* &iter, bool &end_found);
    int execute_statement_body(const Token* &iter, bool &end_found);

    int parse_value(const Token* &iter, Variable* &variable);

    int parse_function(const Token* &iter);

    int parse_expression(const Token* &iter, Variable* &accumulator, bool &result);

    int parse_string(me::string &value, const TokenLocation &location);

  };

}

#endif
