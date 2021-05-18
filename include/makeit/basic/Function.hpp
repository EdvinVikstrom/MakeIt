#ifndef MAKEIT_FUNCTION_HPP
  #define MAKEIT_FUNCTION_HPP

#include "Variable.hpp"
#include "makeit/Logger.hpp"

namespace makeit {

  struct FuncArgument {
    const me::string_view name;
    const Variable::Type type;
  };

  class FuncVariant {

  public:

    const me::uint32_t index;
    const me::vector<FuncArgument> args;

    FuncVariant(me::uint32_t index, const me::vector<FuncArgument> &args);

    bool validate_args(const me::vector<Variable*> &variables) const;

  };

  class Function {

  protected:

    const me::string_view name;
    me::vector<FuncVariant> variants;

  public:

    Function(const me::string_view &name);

    virtual int execute(const FuncVariant &variant, const me::vector<Variable*> &args, class Context &context) = 0;

    const FuncVariant* match_variant(const me::vector<Variable*> &variables) const;

    const me::string_view& get_name() const;
    const me::vector<FuncVariant>& get_variants() const;

  };

  void write_args_to_string(const me::vector<FuncArgument> &arguments, me::string &string);
  void write_vars_to_string(const me::vector<Variable*> &variables, me::string &string);

}

#endif
