#ifndef MAKEIT_FUNCTION_FILES_HPP
  #define MAKEIT_FUNCTION_FILES_HPP

#include "makeit/parser/Context.hpp"

namespace makeit {

  int func_files_init(Context &context);
  int func_files(const me::vector<Variable*> &args, Context &context, void* ptr);

}

#endif
