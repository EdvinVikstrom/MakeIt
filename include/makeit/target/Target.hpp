#ifndef MAKEIT_TARGET_HPP
  #define MAKEIT_TARGET_HPP

#include "makeit/basic/Project.hpp"

namespace makeit {

  class Target {

  protected:

    me::string* output;

  public:

    Target(me::string* output)
      : output(output)
    {
    }

    virtual int generate(const ProjectVar &project) = 0;

  };

}

#endif
