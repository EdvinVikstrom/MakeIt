#ifndef MAKEIT_YCM_TARGET_HPP
  #define MAKEIT_YCM_TARGET_HPP

#include "makeit/basic/Project.hpp"

namespace makeit::ycm {

  int generate(const Project &project, me::string &buffer);

}

#endif
