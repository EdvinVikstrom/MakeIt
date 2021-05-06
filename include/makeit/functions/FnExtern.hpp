#ifndef MAKEIT_FUNCTION_EXTERN_HPP
  #define MAKEIT_FUNCTION_EXTERN_HPP

#include "makeit/parser/Context.hpp"

namespace makeit {

  int func_extern_init(Context &context);
  int func_extern(const me::vector<Variable*> &args, Context &context, void* ptr);

}

#endif
