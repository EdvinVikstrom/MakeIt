#ifndef MAKEIT_TOKEN_HPP
  #define MAKEIT_TOKEN_HPP

#include "makeit/Common.hpp"
#include "makeit/basic/Source.hpp"

namespace makeit {

  enum TokenType {
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_LITERIAL,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_INTEGER,
    TOKEN_TYPE_DECIMAL,
    TOKEN_TYPE_PUNCTUATOR,
    TOKEN_TYPE_QUALIFIER,
    TOKEN_TYPE_STATEMENT,
    TOKEN_TYPE_FUNCTION,
    TOKEN_TYPE_END
  };

  enum CollectionType {
    COLLECTION_TYPE_ARRAY,
    COLLECTION_TYPE_TABLE
  };
  
  enum PunctuatorType {
    PUNCTUATOR_TYPE_EQUAL,
    PUNCTUATOR_TYPE_EQUAL_EQUAL,
    PUNCTUATOR_TYPE_PLUS,
    PUNCTUATOR_TYPE_PLUS_PLUS,
    PUNCTUATOR_TYPE_MINUS,
    PUNCTUATOR_TYPE_MINUS_MINUS,
    PUNCTUATOR_TYPE_STAR,
    PUNCTUATOR_TYPE_SLASH,
    PUNCTUATOR_TYPE_PERCENT,
    PUNCTUATOR_TYPE_PLUS_EQUAL,
    PUNCTUATOR_TYPE_MINUS_EQUAL,
    PUNCTUATOR_TYPE_STAR_EQUAL,
    PUNCTUATOR_TYPE_SLASH_EQUAL,
    PUNCTUATOR_TYPE_PERCENT_EQUAL,
    PUNCTUATOR_TYPE_COLON,
    PUNCTUATOR_TYPE_DOLLAR_SIGN,
    PUNCTUATOR_TYPE_COMMA
  };
  
  
  struct TokenLocation {

    Source source;
    me::string_view pos;

    [[nodiscard]] static inline TokenLocation merge(const TokenLocation &location1, const TokenLocation &location2)
    {
      return {location1.source, {location1.pos.begin(), location2.pos.end()}};
    }

    [[nodiscard]] static inline TokenLocation none()
    {
      return {{"", ""}, ""};
    }

    [[nodiscard]] bool operator==(const TokenLocation &location) const
    {
      return source == location.source && pos == location.pos;
    }

  };

  struct Token {

    TokenType type;
    TokenLocation location;

    inline Token()
    {
    }

    inline Token(TokenType type, const TokenLocation &location)
      : type(type), location(location)
    {
    }

  };

  class LocException : public Exception {

  protected:

    const TokenLocation location;
    char message[1024];

  public:

    inline LocException(const TokenLocation &location, const char* format, ...)
      : location(location)
    {
      va_list args;
      va_start(args, format);
      vsprintf(message, format, args);
      va_end(args);
    }

    inline const TokenLocation& get_location() const
    {
      return location;
    }

    inline const char* get_message() const
    {
      return message;
    }

    void print(FILE* file) const noexcept override;

  };

  
  static inline const char* token_type_name(TokenType type)
  {
    switch (type)
    {
      case TOKEN_TYPE_COMMENT:
        return "COMMENT";
  
      case TOKEN_TYPE_LITERIAL:
        return "LITERIAL";
  
      case TOKEN_TYPE_INTEGER:
        return "INTEGER";
  
      case TOKEN_TYPE_STRING:
        return "STRING";
  
      case TOKEN_TYPE_PUNCTUATOR:
        return "PUNCTUATOR";

      case TOKEN_TYPE_STATEMENT:
        return "STATEMENT";

      case TOKEN_TYPE_FUNCTION:
        return "FUNCTION";
  
      default:
        return "UNKNOWN";
    }
  }
  
}

#endif
