#ifndef MAKEIT_CONTEXT_HPP
  #define MAKEIT_CONTEXT_HPP

#include "Function.hpp"

namespace makeit {

  struct Context {

  public:

    me::map<me::string_view, Variable*> variables;
    me::map<me::string_view, Function*> functions;

    inline void register_function(Function* function)
    {
      functions.put(function->get_name(), function);
    }

  };

}

#endif
