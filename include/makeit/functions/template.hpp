#ifndef MAKEIT_FUNCTION_NAME_HERE_HPP
  #define MAKEIT_FUNCTION_NAME_HERE_HPP

#include "makeit/basic/Context.hpp"

namespace makeit {

  class NameHereFunc : public Function {

  public:

    NameHereFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

}

#endif
