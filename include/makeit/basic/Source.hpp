#ifndef MAKEIT_SOURCE_HPP
  #define MAKEIT_SOURCE_HPP

#include <libme/string.hpp>

namespace makeit {

  struct Source {

    me::string_view name;
    me::string_view data;

    inline bool operator==(const Source &source) const
    {
      return name == source.name;
    }

  };

}

#endif
