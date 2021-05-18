#ifndef MAKEIT_FUNCTION_ADD_INSTALL_HPP
  #define MAKEIT_FUNCTION_ADD_INSTALL_HPP

#include "makeit/basic/Context.hpp"

namespace makeit {

  class AddInstallFunc : public Function {

  public:

    AddInstallFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

}

#endif
