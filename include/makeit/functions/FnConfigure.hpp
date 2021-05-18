#ifndef MAKEIT_FUNCTION_CONFIGURE_HPP
  #define MAKEIT_FUNCTION_CONFIGURE_HPP

#include "makeit/basic/Context.hpp"

namespace makeit {

  class ConfigureFunc : public Function {

  public:

    ConfigureFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

}

#endif
