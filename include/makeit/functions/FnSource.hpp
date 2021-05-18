#ifndef MAKEIT_FUNCTION_SOURCE_HPP
  #define MAKEIT_FUNCTION_SOURCE_HPP

#include "makeit/basic/Context.hpp"

namespace makeit {

  class SourceFunc : public Function {

  public:

    SourceFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

}

#endif
