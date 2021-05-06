#ifndef MAKEIT_COMMON_HPP
  #define MAKEIT_COMMON_HPP

#include <libme/type.hpp>

#include <stdio.h>
#include <libintl.h>

#define _(s) gettext(s)

namespace makeit {

  class Exception {

  public:

    virtual void print(FILE* file) const noexcept = 0;

  };

  class RuntimeException {

  protected:

    char message[1024];

  public:

    inline RuntimeException(const char* format, ...)
    {
      va_list args;
      va_start(args, format);
      vsprintf(message, format, args);
      va_end(args);
    }

    inline const char* get_message() const
    {
      return message;
    }

  };

  static inline void get_line_and_column(const char* begin, const char* end, me::size_t &line, me::size_t &column)
  {
    line = 1;
    column = 1;
  
    while (begin != end)
    {
      if (*begin == '\n')
      {
        column = 1;
        line++;
      }else
        column++;
  
      begin++;
    }
  }

}

#endif
