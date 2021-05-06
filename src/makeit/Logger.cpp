#include "makeit/Logger.hpp"

#include <stdarg.h>

makeit::Logger::Logger(FILE* file)
  : file(file)
{
}

int makeit::Logger::print(const char* format, ...) const
{
  va_list args;
  va_start(args, format);
  vfprintf(file, format, args);
  va_end(args);
  return 0;
}

int makeit::Logger::fatal(const char* format, ...) const
{
  va_list args;
  va_start(args, format);
  printf("\e[31mfatal:\e[0m ");
  vfprintf(file, format, args);
  va_end(args);
  return 0;
}

int makeit::Logger::error(const char* format, ...) const
{
  va_list args;
  va_start(args, format);
  printf("\e[31merror:\e[0m ");
  vfprintf(file, format, args);
  va_end(args);
  return 0;
}

int makeit::Logger::warning(const char* format, ...) const
{
  va_list args;
  va_start(args, format);
  printf("\e[33mwarning:\e[0m ");
  vfprintf(file, format, args);
  va_end(args);
  return 0;
}

int makeit::Logger::debug(const char* format, ...) const
{
  va_list args;
  va_start(args, format);
  printf("\e[30mdebug:\e[0m ");
  vfprintf(file, format, args);
  va_end(args);
  return 0;
}

int makeit::Logger::trace(const TokenLocation &location, const char* format, ...) const
{
  char name_cstr[location.source.name.size() + 1];
  location.source.name.c_str(name_cstr);

  size_t line, column;
  get_line_and_column(location.pos.begin(), location.pos.end(), line, column);

  va_list args;
  va_start(args, format);
  printf("\e[97m%s:%lu:%lu\e[0m \e[90m", name_cstr, line, column);
  vfprintf(file, format, args);
  printf("\e[0m\n");
  va_end(args);
  return 0;
}

int makeit::Logger::trace(const char* format, ...) const
{
  va_list args;
  va_start(args, format);
  printf("\e[90m");
  vfprintf(file, format, args);
  printf("\e[0m\n");
  va_end(args);
  return 0;
}
