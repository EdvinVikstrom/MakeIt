#include "makeit/lexer/Lexer.hpp"

#define LEXER_IS_COMMENT_CHAR(c) ((c) == '#')
#define LEXER_COMMENT_END_CHAR(c) (c == '#' ? '\n' : '\n')
#define LEXER_IS_LITERIAL_CHAR(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z') || (c) == '_' || (c) == '.')
#define LEXER_IS_DIGIT_CHAR(c) ((c) >= '0' && (c) <= '9')
#define LEXER_IS_STRING_CHAR(c) ((c) == '"' || (c) == '\'')
#define LEXER_STRING_END_CHAR(c) ((c) == '"' ? '"' : '\'')
#define LEXER_IS_PUNCTUATOR_CHAR(c) ((c) == '=' || (c) == '+' || (c) == '-' || (c) == '*' || (c) == '/' || (c) == '%' || \
    (c) == ':' || (c) == ',' || (c) == '[' || (c) == ']' || (c) == '{' || (c) == '}' || (c) == '?')
#define LEXER_IS_STATEMENT(s) ((s) == "if" || (s) == "elif" || (s) == "for" || (s) == "while" || (s) == "then" || (s) == "end" || \
    (s) == "and" || (s) == "or")
#define LEXER_IS_QUALIFIER(s) ((s) == "const")

makeit::Lexer::Lexer(const Logger &logger)
  : logger(logger)
{
}

int makeit::Lexer::lexify(const MakeItSource &source, me::vector<Token> &tokens) const
{
  me::size_t token_count;
  seek_tokens(source, token_count, '\0');

  me::size_t offset = tokens.size();
  tokens.resize(token_count + offset);
  make_tokens(source, token_count, tokens.data() + offset);
  tokens.push_back(Token{TOKEN_TYPE_END, {}});
  return 0;
}

int makeit::Lexer::seek_token(const char* &iter, Token &token) const
{
  /* comment token */
  if (LEXER_IS_COMMENT_CHAR(*iter))
  {
    char end_char = LEXER_COMMENT_END_CHAR(*iter);

    const char* begin = iter;

    while (*iter != '\0' && *iter++ != end_char);

    token.location.pos = {begin, iter};

    token.type = TOKEN_TYPE_COMMENT;

  /* literial token */
  }else if (LEXER_IS_LITERIAL_CHAR(*iter))
  {
    const char* begin = iter;

    bool accept_digits = false;
    while (*iter != '\0' && (LEXER_IS_LITERIAL_CHAR(*iter) || (accept_digits && LEXER_IS_DIGIT_CHAR(*iter))))
    {
      iter++;

      /* Accept digits after the first character */
      accept_digits = true;
    }

    token.location.pos = {begin, iter};

    if (LEXER_IS_STATEMENT(token.location.pos))
    {
      token.type = TOKEN_TYPE_STATEMENT;
    }else if (LEXER_IS_QUALIFIER(token.location.pos))
    {
      token.type = TOKEN_TYPE_QUALIFIER;
    }else if (*iter == ':')
    {
      iter++;
      token.type = TOKEN_TYPE_FUNCTION;
    }else
    {
      token.type = TOKEN_TYPE_LITERIAL;
    }

  /* integer token */
  }else if (LEXER_IS_DIGIT_CHAR(*iter))
  {
    const char* begin = iter;

    iter++;

    token.location.pos = {begin, iter};

    token.type = TOKEN_TYPE_INTEGER;

  /* string token */
  }else if (LEXER_IS_STRING_CHAR(*iter))
  {
    char end_char = LEXER_STRING_END_CHAR(*iter);

    const char* begin = iter;

    iter++; /* skipping string prefix */
    while (*iter != '\0' && *iter++ != end_char);

    token.location.pos = {begin, iter};

    token.type = TOKEN_TYPE_STRING;

  /* punctuator token */
  }else if (LEXER_IS_PUNCTUATOR_CHAR(*iter))
  {
    const char* begin = iter;

    if (*iter == '=' && *(iter + 1) == '=')
      iter += 2;
    else if (*iter == '?' && *(iter + 1) == '=')
      iter += 2;
    else if (*iter == '+' && *(iter + 1) == '=')
      iter += 2;
    else if (*iter == '-' && *(iter + 1) == '=')
      iter += 2;
    else if (*iter == '*' && *(iter + 1) == '=')
      iter += 2;
    else if (*iter == '/' && *(iter + 1) == '=')
      iter += 2;
    else if (*iter == '%' && *(iter + 1) == '=')
      iter += 2;
    else
      iter += 1;

    token.location.pos = {begin, iter};

    token.type = TOKEN_TYPE_PUNCTUATOR;

  /* unknown character */
  }else
  {
    throw LocException(TokenLocation{token.location.file, token.location.data, {iter, iter + 1}},
	"Unknown character '%c'", *iter);
  }
  return 0;
}

int makeit::Lexer::seek_tokens(const MakeItSource &source, me::size_t &count, char end_char) const
{
  const char* iter = source.data.begin();

  count = 0;
  while (*iter != '\0')
  {
    if (!skip_whitespace(iter))
      break;

    if (end_char == *iter)
      break;

    Token temp;
    temp.location.file = source.name;
    temp.location.data = source.data;
    seek_token(iter, temp);
    count++;
  }
  return 0;
}

int makeit::Lexer::make_tokens(const MakeItSource &source, me::size_t count, Token* tokens) const
{
  const char* iter = source.data.begin();

  me::size_t index = 0;
  while (index < count)
  {
    if (!skip_whitespace(iter))
      break;

    Token &token = tokens[index++];
    token.location.file = source.name;
    token.location.data = source.data;
    seek_token(iter, token);
  }
  return 0;
}

bool makeit::Lexer::skip_whitespace(const char* &iter) const noexcept
{
  while (*iter != '\0')
  {
    if (!(*iter == ' ' || *iter == '\t' || *iter == '\n'))
      break;
    iter++;
  }

  return *iter != '\0';
}
