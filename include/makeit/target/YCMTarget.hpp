#ifndef MAKEIT_YCM_TARGET_HPP
  #define MAKEIT_YCM_TARGET_HPP

#include "Target.hpp"

namespace makeit {

  class YCMTarget : public Target {

  public:

    YCMTarget(me::string* output)
      : Target(output)
    {
    }

    int generate(const ProjectVar &project) override;

    int write_cflags(const ProjectVar &project);
    int write_files(const ProjectVar &project);

  };

}

#endif
