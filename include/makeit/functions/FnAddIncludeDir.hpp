#ifndef MAKEIT_FUNCTION_ADD_INCLUDE_DIRECTORY_HPP
  #define MAKEIT_FUNCTION_ADD_INCLUDE_DIRECTORY_HPP

#include "makeit/parser/Context.hpp"

namespace makeit {

  int func_add_include_directory_init(Context &context);
  int func_add_include_directory(const me::vector<Variable*> &args, Context &context, void* ptr);

}

#endif
