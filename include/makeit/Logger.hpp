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

    const Logger& printf(const char* format, ...) const;

    const Logger& fatal(const char* format, ...) const;

    const Logger& error(const char* format, ...) const;

    const Logger& warning(const char* format, ...) const;

    const Logger& debug(const char* format, ...) const;

    const Logger& trace(const char* format, ...) const;

    const Logger& location(const TokenLocation &location) const;

  };

}

#endif
