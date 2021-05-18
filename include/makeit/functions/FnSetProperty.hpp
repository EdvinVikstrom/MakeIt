#ifndef MAKEIT_FUNCTION_SET_PROPERTY_HPP
  #define MAKEIT_FUNCTION_SET_PROPERTY_HPP

#include "makeit/basic/Context.hpp"

namespace makeit {

  class SetBuildDirectoryFunc : public Function {

  public:

    SetBuildDirectoryFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

  class SetBinaryDirectoryFunc : public Function {

  public:

    SetBinaryDirectoryFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

  class SetOutputFunc : public Function {

  public:

    SetOutputFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

  class SetLanguageFunc : public Function {

  public:

    SetLanguageFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

  class SetKindFunc : public Function {

  public:

    SetKindFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

  class SetCompilerFunc : public Function {

  public:

    SetCompilerFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

  class SetLinkerFunc : public Function {

  public:

    SetLinkerFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

  class SetSystemRootFunc : public Function {

  public:

    SetSystemRootFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

  class SetTargetArchFunc : public Function {

  public:

    SetTargetArchFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

}

#endif
