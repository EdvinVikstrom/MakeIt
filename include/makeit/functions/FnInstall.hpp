#ifndef MAKEIT_FUNCTION_INSTALL_HPP
  #define MAKEIT_FUNCTION_INSTALL_HPP

#include "makeit/parser/Context.hpp"

namespace makeit {

  int func_install_init(Context &context);
  int func_install(const me::vector<Variable*> &args, Context &context, void* ptr);

}

#endif
