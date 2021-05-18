#ifndef MAKEIT_CONFIG_HPP
  #define MAKEIT_CONFIG_HPP

#include <libme/string.hpp>

namespace makeit {

  struct Config {
    /* defaults */
    me::string_view compiler;
    me::string_view linker;
    me::string_view build_path;
    me::string_view config_file;
    me::string_view source_file;
  };

  extern Config config;

}

#endif
