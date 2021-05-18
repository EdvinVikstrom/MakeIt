#ifndef MAKEIT_FUNCTION_ADD_EXTERN_HPP
  #define MAKEIT_FUNCTION_ADD_EXTERN_HPP

#include "makeit/basic/Context.hpp"

namespace makeit {

  class AddExternFunc : public Function {

  public:

    AddExternFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

}

#endif
