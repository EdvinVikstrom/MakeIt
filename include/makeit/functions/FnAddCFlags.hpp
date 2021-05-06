#ifndef MAKEIT_FUNCTION_ADD_CFLAGS_HPP
  #define MAKEIT_FUNCTION_ADD_CFLAGS_HPP

#include "makeit/parser/Context.hpp"

namespace makeit {

  int func_add_cflags_init(Context &context);
  int func_add_cflags(const me::vector<Variable*> &args, Context &context, void* ptr);

}

#endif
