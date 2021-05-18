#include "makeit/lexer/Token.hpp"

void makeit::LocException::print(FILE* file) const noexcept
{
  size_t line, column;
  get_line_and_column(location.data.begin(), location.pos.begin(), line, column);

  char temp[location.file.size() + 1];
  fprintf(file, "\e[97m%s:%lu:%lu:\e[0m %s\n", location.file.c_str(temp), line, column, message);
}
