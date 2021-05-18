#ifndef MAKEIT_VARIABLE_HPP
  #define MAKEIT_VARIABLE_HPP

#include "makeit/Common.hpp"
#include "makeit/lexer/Token.hpp"

#include <libme/map.hpp>
#include <libme/vector.hpp>
#include <libme/string.hpp>

namespace makeit {

  class Variable {

  public:

    enum Type {
      TEMP, STRING, INTEGER,
      DECIMAL, ARRAY, TABLE, STRUCT
    };

    const Type type;

    Variable(Type type)
      : type(type)
    {
    }

    virtual void copy(Variable* &var, me::allocator &alloc) const = 0;
    virtual void assign(Variable* var) = 0;
    virtual void append(Variable* var) = 0;
    virtual bool compare(Variable* var) const = 0;
    virtual me::string as_string() const = 0;

  };

  class TempVar : public Variable {
  public:
    typedef me::string_view Value;
    Value value;
    TempVar(const Value &value);
    void copy(Variable* &var, me::allocator &alloc) const override;
    void assign(Variable* var) override;
    void append(Variable* var) override;
    bool compare(Variable* var) const override;
    me::string as_string() const override;
  };

  class StringVar : public Variable {
  public:
    typedef me::string Value;
    Value value;
    StringVar(const Value &value);
    void copy(Variable* &var, me::allocator &alloc) const override;
    void assign(Variable* var) override;
    void append(Variable* var) override;
    bool compare(Variable* var) const override;
    me::string as_string() const override;
  };

  class IntegerVar : public Variable {
  public:
    typedef int Value;
    Value value;
    IntegerVar(const Value &value);
    void copy(Variable* &var, me::allocator &alloc) const override;
    void assign(Variable* var) override;
    void append(Variable* var) override;
    bool compare(Variable* var) const override;
    me::string as_string() const override;
  };

  class DecimalVar : public Variable {
  public:
    typedef float Value;
    Value value;
    DecimalVar(const Value &value);
    void copy(Variable* &var, me::allocator &alloc) const override;
    void assign(Variable* var) override;
    void append(Variable* var) override;
    bool compare(Variable* var) const override;
    me::string as_string() const override;
  };

  class ArrayVar : public Variable {
  public:
    typedef me::vector<Variable*> Value;
    Value value;
    ArrayVar(const Value &value);
    void copy(Variable* &var, me::allocator &alloc) const override;
    void assign(Variable* var) override;
    void append(Variable* var) override;
    bool compare(Variable* var) const override;
    me::string as_string() const override;
  };

  class TableVar : public Variable {
  public:
    typedef me::map<me::string_view, Variable*> Value;
    Value value;
    TableVar(const Value &value);
    void copy(Variable* &var, me::allocator &alloc) const override;
    void assign(Variable* var) override;
    void append(Variable* var) override;
    bool compare(Variable* var) const override;
    me::string as_string() const override;
  };

  class StructVar : public Variable {
  public:
    typedef me::string_view Value;
    Value value;
    StructVar(const Value &value);
    void copy(Variable* &var, me::allocator &alloc) const override;
    void assign(Variable* var) override;
    void append(Variable* var) override;
    bool compare(Variable* var) const override;
    me::string as_string() const override;
  };

  const char* variable_type_name(Variable::Type type);

}

#endif
