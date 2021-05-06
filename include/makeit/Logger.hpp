#ifndef MAKEIT_LOGGER_HPP
  #define MAKEIT_LOGGER_HPP

#include "lexer/Token.hpp"

#include <stdio.h>

namespace makeit {

  class Logger {

  protected:

    FILE* file;

  public:

    Logger(FILE* file);

    int print(const char* format, ...) const;

    int fatal(const char* format, ...) const;

    int error(const char* format, ...) const;

    int warning(const char* format, ...) const;

    int debug(const char* format, ...) const;

    int trace(const TokenLocation &location, const char* format, ...) const;

    int trace(const char* format, ...) const;

  };

}

#endif
