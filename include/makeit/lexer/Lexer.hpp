#ifndef MAKEIT_LEXER_HPP
  #define MAKEIT_LEXER_HPP

#include "makeit/Logger.hpp"
#include "Token.hpp"

#include <libme/vector.hpp>

namespace makeit {

  class Lexer {

  protected:

    const Logger &logger;

  public:

    Lexer(const Logger &logger);

    /* converts the source into tokens with a single function */
    int lexify(const Source &source, me::vector<Token> &tokens) const;

    /* seek next token */
    int seek_token(const char* &iter, Token &token) const;

    /* finding the amount of tokens in the source.
     * ends if 'end_char' is present */
    int seek_tokens(const Source &source, me::size_t &count, char end_char) const;

    /* read every next token within 'count' */
    int make_tokens(const Source &source, me::size_t count, Token* tokens) const;

    /* skips 'space', 'new line' and 'tab' characters.
     * returns false if theres no more data to read */
    bool skip_whitespace(const char* &iter) const noexcept;

  };

}

#endif
