#ifndef MAKEIT_FUNCTION_SOURCE_HPP
  #define MAKEIT_FUNCTION_SOURCE_HPP

#include "makeit/parser/Context.hpp"

namespace makeit {

  int func_source_init(Context &context);
  int func_source(const me::vector<Variable*> &args, Context &context, void* ptr);

}

#endif
