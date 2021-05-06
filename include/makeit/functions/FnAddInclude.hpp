#ifndef MAKEIT_FUNCTION_ADD_INCLUDE_HPP
  #define MAKEIT_FUNCTION_ADD_INCLUDE_HPP

#include "makeit/parser/Context.hpp"

namespace makeit {

  int func_add_include_init(Context &context);
  int func_add_include(const me::vector<Variable*> &args, Context &context, void* ptr);

}

#endif
