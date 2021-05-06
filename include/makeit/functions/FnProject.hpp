#ifndef MAKEIT_FUNCTION_PROJECT_HPP
  #define MAKEIT_FUNCTION_PROJECT_HPP

#include "makeit/parser/Context.hpp"

namespace makeit {

  int func_project_init(Context &context);
  int func_project(const me::vector<Variable*> &args, Context &context, void* ptr);

}

#endif
