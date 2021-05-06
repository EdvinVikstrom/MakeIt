#ifndef MAKEIT_FUNCTION_ADD_LFLAGS_HPP
  #define MAKEIT_FUNCTION_ADD_LFLAGS_HPP

#include "makeit/parser/Context.hpp"

namespace makeit {

  int func_add_lflags_init(Context &context);
  int func_add_lflags(const me::vector<Variable*> &args, Context &context, void* ptr);

}

#endif
