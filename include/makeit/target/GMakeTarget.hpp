#ifndef MAKEIT_GMAKE_TARGET_HPP
  #define MAKEIT_GMAKE_TARGET_HPP

#include "makeit/basic/Project.hpp"

namespace makeit::gmake {

  int generate(const Project &project, me::string &buffer);

}

#endif
