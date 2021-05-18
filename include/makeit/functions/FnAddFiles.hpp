#ifndef MAKEIT_FUNCTION_ADD_FILES_HPP
  #define MAKEIT_FUNCTION_ADD_FILES_HPP

#include "makeit/basic/Context.hpp"

namespace makeit {

  class AddFilesFunc : public Function {

  public:

    AddFilesFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

}

#endif
