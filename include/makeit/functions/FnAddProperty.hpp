#ifndef MAKEIT_FUNCTION_ADD_PROPERTY_HPP
  #define MAKEIT_FUNCTION_ADD_PROPERTY_HPP

#include "makeit/basic/Context.hpp"

namespace makeit {

  class AddCFlagsFunc : public Function {

  public:

    AddCFlagsFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

  class AddLFlagsFunc : public Function {

  public:

    AddLFlagsFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

  class AddFlagsFunc : public Function {

  public:

    AddFlagsFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

  class AddIncludeFunc : public Function {

  public:

    AddIncludeFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

  class AddIncludePathFunc : public Function {

  public:

    AddIncludePathFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

  class AddLibraryFunc : public Function {

  public:

    AddLibraryFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

  class AddLibraryPathFunc : public Function {

  public:

    AddLibraryPathFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

  class AddPackageFunc : public Function {

  public:

    AddPackageFunc();

    int execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context) override;

  };

}

#endif
