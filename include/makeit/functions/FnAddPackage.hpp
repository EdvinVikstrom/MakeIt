#ifndef MAKEIT_FUNCTION_ADD_PACKAGE_HPP
  #define MAKEIT_FUNCTION_ADD_PACKAGE_HPP

#include "makeit/parser/Context.hpp"

namespace makeit {

  int func_add_package_init(Context &context);
  int func_add_package(const me::vector<Variable*> &args, Context &context, void* ptr);

}

#endif
