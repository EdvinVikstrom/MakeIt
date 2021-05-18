#ifndef MAKEIT_BUILD_CONFIG_HPP
  #define MAKEIT_BUILD_CONFIG_HPP

#include <libme/string.hpp>
#include <libme/vector.hpp>

namespace makeit {

  enum Language {
    LANGUAGE_INVALID = 1,
    LANGUAGE_C = (1 << 1),
    LANGUAGE_CXX = (1 << 2),
    LANGUAGE_OBJECTIVE_C = (1 << 3),
    LANGUAGE_ALL = LANGUAGE_C | LANGUAGE_CXX | LANGUAGE_OBJECTIVE_C
  };

  enum Kind {
    KIND_EXECUTABLE,
    KIND_STATIC_LIBRARY,
    KIND_SHARED_LIBRARY
  };


  struct Builder;
  struct Linker;
  struct Compiler;
  struct BuildConfig;
  struct LinkConfig;
  struct CompileConfig;
  struct Warnings;
  struct SystemRoot;
  struct TargetArch;
  struct Package;
  struct Library;
  struct LibraryPath;
  struct Include;
  struct IncludePath;


  /* Linker stuff */
  struct Linker {
    me::string_view name;
    me::string_view directory;

    void write(me::string &buffer) const;
  };

  struct Library {
    enum Type { STATIC, SHARED } type;
    me::string_view name;

    inline Library(Type type, const me::string_view &name)
      : type(type), name(name) { }

    void write(me::string &buffer, const Linker &linker) const;
  };

  struct LibraryPath {
    me::string_view path;

    inline LibraryPath(const me::string_view &path)
      : path(path) { }

    void write(me::string &buffer, const Linker &linker) const;
  };

  struct LinkConfig {
    Linker linker;
    me::vector<me::string_view> options;
    me::vector<Library> libraries;
    me::vector<LibraryPath> library_paths;

    void write(me::string &buffer, const Builder &builder) const;
  };
  /* ------------ */


  /* Compiler stuff */
  struct Compiler {
    me::string_view name;
    me::string_view directory;

    void write(me::string &buffer) const;
  };

  struct Include {
    me::string_view path;

    inline Include(const me::string_view &path)
      : path(path) { }

    void write(me::string &buffer, const Compiler &compiler) const;
  };

  struct IncludePath {
    me::string_view path;

    inline IncludePath(const me::string_view &path)
      : path(path) { }

    void write(me::string &buffer, const Compiler &compiler) const;
  };

  struct CompileConfig {
    Compiler compiler;
    me::vector<me::string_view> options;
    me::vector<Include> includes;
    me::vector<IncludePath> include_paths;

    void write(me::string &buffer, const Builder &builder) const;
  };
  /* -------------- */


  /* Build stuff */
  struct Builder {
    /* Struct for storing a type for every supported language */
    template<typename T>
    struct TypeLang {
      T lang_c, lang_cxx, lang_objc;
      constexpr void for_each(int langs, auto func)
      {
	if (langs & LANGUAGE_C) func(lang_c, LANGUAGE_C);
	if (langs & LANGUAGE_CXX) func(lang_cxx, LANGUAGE_CXX);
	if (langs & LANGUAGE_OBJECTIVE_C) func(lang_objc, LANGUAGE_OBJECTIVE_C);
      }
    };

    me::string_view directory;
    me::string_view output;
    Language lang = LANGUAGE_C;
    Kind kind = KIND_EXECUTABLE;
    LinkConfig link_config;
    TypeLang<CompileConfig> compile_config;

    void write(me::string &buffer) const;
  };

  struct Warnings {
    enum { ALL } type;
    me::uint64_t enabled;

    void write(me::string &buffer, const Builder &builder) const;
  };

  struct SystemRoot {
    me::string_view path;

    void write(me::string &buffer, const Builder &builder) const;
  };

  struct TargetArch {
    me::string_view arch;

    void write(me::string &buffer, const Builder &builder) const;
  };

  struct Package {

    inline Package()
    { }

    void write(me::string &buffer, const Builder &builder) const;
  };

  struct BuildConfig {
    Builder builder;
    me::vector<me::string_view> options;
    Warnings warnings;
    SystemRoot system_root;
    TargetArch target_arch;
    me::vector<Package> packages;

    void write(me::string &buffer) const;
    void validate();
  };
  /* ----------- */

  Language language_from_string(const me::string_view &str);
  Kind kind_from_string(const me::string_view &str);
  me::string_view identify_compiler_name(const me::string_view &name, Language lang);
  me::string_view identify_linker_name(const me::string_view &name, Language lang);

}

#endif
