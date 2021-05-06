#ifndef MAKEIT_FUNCTION_HPP
  #define MAKEIT_FUNCTION_HPP

#include "Variable.hpp"
#include "makeit/Logger.hpp"

namespace makeit {

  struct ArgConfig {
    const Variable::Type type;
    ArgConfig(Variable::Type type)
      : type(type)
    {
    }
    int validate(const Variable* var, Logger &logger) const;
  };

  struct TextArg : public ArgConfig {
    const me::vector<me::string_view> valid; /* If size is 0 then ignore to validate */
    TextArg(const me::vector<me::string_view> &valid)
      : ArgConfig(Variable::TEXT), valid(valid)
    {
    }
    int validate(const TextVar* var, Logger &logger) const;
  };

  struct StringArg : public ArgConfig {
    const me::size_t min_len, max_len;
    StringArg(me::size_t min_len, me::size_t max_len)
      : ArgConfig(Variable::STRING), min_len(min_len), max_len(max_len)
    {
    }
    StringArg()
      : ArgConfig(Variable::STRING), min_len(0x0000), max_len(0xFFFF)
    {
    }
    int validate(const StringVar* var, Logger &logger) const;
  };

  struct IntegerArg : public ArgConfig {
    const IntegerVar::Value min_num, max_num;
    IntegerArg(IntegerVar::Value min_num, IntegerVar::Value max_num)
      : ArgConfig(Variable::INTEGER), min_num(min_num), max_num(max_num)
    {
    }
    int validate(const IntegerVar* var, Logger &logger) const;
  };

  struct DecimalArg : public ArgConfig {
    const DecimalVar::Value min_num, max_num;
    DecimalArg(DecimalVar::Value min_num, DecimalVar::Value max_num)
      : ArgConfig(Variable::DECIMAL), min_num(min_num), max_num(max_num)
    {
    }
    int validate(const DecimalVar* var, Logger &logger) const;
  };

  struct ArrayArg : public ArgConfig {
    const ArgConfig* element_config;
    ArrayArg(const ArgConfig* element_config)
      : ArgConfig(Variable::ARRAY), element_config(element_config)
    {
    }
    int validate(const ArrayVar* var, Logger &logger) const;
  };

  struct TableArg : public ArgConfig {
    struct Entry { ArgConfig* config; bool required; };
    const me::map<me::string_view, Entry> layout;
    TableArg(const me::map<me::string_view, Entry> &layout)
      : ArgConfig(Variable::TABLE), layout(layout)
    {
    }
    int validate(const TableVar* var, Logger &logger) const;
  };

  struct StructArg : public ArgConfig {
    const me::string_view name; /* If size is 0 then ignore to validate */
    StructArg(const me::string_view &name)
      : ArgConfig(Variable::STRUCT), name(name)
    {
    }
    int validate(const StructVar* var, Logger &logger) const;
  };



  struct Function {

    typedef me::shared_ptr<Function> Pointer;

    typedef int (Fn) (const me::vector<Variable*> &args, struct Context &context, void* ptr);

    const me::vector<ArgConfig*> args;
    Fn* func;

  };

}

#endif
