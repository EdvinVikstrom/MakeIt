#ifndef MAKEIT_FUNCTION_ADD_DEFINE_HPP
  #define MAKEIT_FUNCTION_ADD_DEFINE_HPP

#include "makeit/parser/Context.hpp"

namespace makeit {

  int func_add_define_init(Context &context);
  int func_add_define(const me::vector<Variable*> &args, Context &context, void* ptr);

}

#endif
