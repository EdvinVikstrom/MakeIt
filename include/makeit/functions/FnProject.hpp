#ifndef MAKEIT_FUNCTION_PROJECT_HPP
  #define MAKEIT_FUNCTION_PROJECT_HPP

#include "makeit/basic/Context.hpp"

namespace makeit {

  class ProjectFunc : public Function {

  public:

    ProjectFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

}

#endif
