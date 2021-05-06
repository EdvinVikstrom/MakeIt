#ifndef MAKEIT_CONTEXT_HPP
  #define MAKEIT_CONTEXT_HPP

#include "makeit/basic/Function.hpp"

namespace makeit {

  struct Context {
    void* func_user_ptr;
    me::map<me::string_view, Variable*> variables;
    me::map<me::string_view, Function*> functions;
  };

}

#endif
