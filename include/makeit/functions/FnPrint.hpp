#ifndef MAKEIT_FUNCTION_PRINT_HPP
  #define MAKEIT_FUNCTION_PRINT_HPP

#include "makeit/basic/Context.hpp"

namespace makeit {

  class PrintFunc : public Function {

  public:

    PrintFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

}

#endif
