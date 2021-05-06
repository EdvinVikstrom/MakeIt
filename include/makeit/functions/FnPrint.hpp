#ifndef MAKEIT_FUNCTION_PRINT_HPP
  #define MAKEIT_FUNCTION_PRINT_HPP

#include "makeit/parser/Context.hpp"

namespace makeit {

  int func_print_init(Context &context);
  int func_print(const me::vector<Variable*> &args, Context &context, void* ptr);

}

#endif
