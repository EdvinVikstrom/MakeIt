#ifndef MAKEIT_FUNCTION_ADD_LIBRARY_DIRECTORY_HPP
  #define MAKEIT_FUNCTION_ADD_LIBRARY_DIRECTORY_HPP

#include "makeit/parser/Context.hpp"

namespace makeit {

  int func_add_library_directory_init(Context &context);
  int func_add_library_directory(const me::vector<Variable*> &args, Context &context, void* ptr);

}

#endif
