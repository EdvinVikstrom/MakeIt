#ifndef MAKEIT_CONFIG_HPP
  #define MAKEIT_CONFIG_HPP

#include <libme/string.hpp>

namespace makeit {

  struct Config {
    me::string config_file;
    me::string source_file;
  };

}

#endif
