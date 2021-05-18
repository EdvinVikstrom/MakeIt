#ifndef MAKEIT_PROJECT_HPP
  #define MAKEIT_PROJECT_HPP

#include "BuildConfig.hpp"

#include <libme/vector.hpp>
#include <libme/map.hpp>

namespace makeit {

  struct Source {
    const me::string_view source;
    const Language language;
    CompileConfig config;

    Source(const me::string_view &source);
    Source(const me::string_view &source, Language language);

    char* string_write(char* buffer) const;
    me::string& string_write(me::string &buffer) const;

    char* string_write(const me::string_view &build_directory, char* buffer) const;
    me::string& string_write(const me::string_view &build_directory, me::string &buffer) const;

    static constexpr const me::string_view OBJECT_SUFFIX = "o";
  };

  struct External {
    const me::string_view command;
    const me::string_view output;
    me::vector<me::string_view> options;

    External(const me::string_view &command, const me::string_view &output);
  };

  struct Installation {
    const me::string_view source;
    const me::string_view directory;

    Installation(const me::string_view &source, const me::string_view &directory);
  };

  struct Project {
    me::string_view name;
    me::string_view version;
    BuildConfig build_config;
    me::vector<Source> sources;
    me::vector<External> externals;
    me::vector<Installation> installations;
  };

  extern Project project;

  Language identify_file(const me::string_view &file);


}

#endif
