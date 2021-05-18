#include "makeit/Logger.hpp"

#include <stdarg.h>

makeit::Logger::Logger(FILE* file)
  : file(file)
{
}

const makeit::Logger& makeit::Logger::printf(const char* format, ...) const
{
  va_list args;
  va_start(args, format);
  vfprintf(file, format, args);
  va_end(args);
  return *this;
}

const makeit::Logger& makeit::Logger::fatal(const char* format, ...) const
{
  va_list args;
  va_start(args, format);
  printf("\e[31mfatal:\e[0m ");
  vfprintf(file, format, args);
  va_end(args);
  return *this;
}

const makeit::Logger& makeit::Logger::error(const char* format, ...) const
{
  va_list args;
  va_start(args, format);
  printf("\e[31merror:\e[0m ");
  vfprintf(file, format, args);
  va_end(args);
  return *this;
}

const makeit::Logger& makeit::Logger::warning(const char* format, ...) const
{
  va_list args;
  va_start(args, format);
  printf("\e[33mwarning:\e[0m ");
  vfprintf(file, format, args);
  va_end(args);
  return *this;
}

const makeit::Logger& makeit::Logger::debug(const char* format, ...) const
{
  va_list args;
  va_start(args, format);
  printf("\e[30mdebug:\e[0m ");
  vfprintf(file, format, args);
  va_end(args);
  return *this;
}

const makeit::Logger& makeit::Logger::trace(const char* format, ...) const
{
  va_list args;
  va_start(args, format);
  printf("\e[90m");
  vfprintf(file, format, args);
  printf("\e[0m\n");
  va_end(args);
  return *this;
}

const makeit::Logger& makeit::Logger::location(const TokenLocation &location) const
{
  char name_cstr[location.file.size() + 1];
  location.file.c_str(name_cstr);

  size_t line, column;
  get_line_and_column(location.data.begin(), location.pos.end(), line, column);

  printf("\e[97m%s:%lu:%lu\e[0m ", name_cstr, line, column);
  return *this;
}
