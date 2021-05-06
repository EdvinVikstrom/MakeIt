#ifndef MAKEIT_GMAKE_TARGET_HPP
  #define MAKEIT_GMAKE_TARGET_HPP

#include "Target.hpp"

namespace makeit {

  class GMakeTarget : public Target {

  public:

    GMakeTarget(me::string *output)
      : Target(output)
    {
    }

    int generate(const ProjectVar &project) override;

    int write_cflags(const ProjectVar &project);
    int write_lflags(const ProjectVar &project);
    int write_files(const ProjectVar &project);
    int write_externs(const ProjectVar &project);

    int write_rule_main(const ProjectVar &project);
    int write_rule_link(const ProjectVar &project);
    int write_rule_files(const ProjectVar &project);
    int write_rule_externs(const ProjectVar &project);
    int write_rule_installs(const ProjectVar &project);
    int write_rule_clean(const ProjectVar &project);

  };

}

#endif
