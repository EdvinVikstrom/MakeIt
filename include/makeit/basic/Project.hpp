#ifndef MAKEIT_PROJECT_HPP
  #define MAKEIT_PROJECT_HPP

#include "makeit/Text.hpp"
#include "Variable.hpp"

namespace makeit {

  enum Kind {
    KIND_EXECUTABLE = 0x01,
    KIND_STATIC_LIBRARY = 0x02,
    KIND_SHARED_LIBRARY = 0x04,
    KIND_NONE = 0x00
  };

  enum Lang {
    LANG_C = 0x01,
    LANG_CXX = 0x02,
    LANG_OBJC = 0x04,
    LANG_NONE = 0x00
  };

  enum CC {
    CC_GNU = 0x01,
    CC_LLVM = 0x02,
    CC_NONE = 0x00
  };

  enum LibraryType {
    LIBRARY_TYPE_STATIC = 0x01,
    LIBRARY_TYPE_SHARED = 0x02,
    LIBRARY_TYPE_NONE = 0x00
  };

  enum ExternType {
    EXTERN_TYPE_CMAKE = 0x01,
    EXTERN_TYPE_GMAKE = 0x02,
    EXTERN_TYPE_PREMAKE = 0x04,
    EXTERN_TYPE_MESON = 0x08,
    EXTERN_TYPE_NINJA = 0x10,
    EXTERN_TYPE_MAKEIT = 0x20,
    EXTERN_TYPE_NONE = 0x00
  };

  enum TargetType {
    TARGET_TYPE_GMAKE = 0x01,
    TARGET_TYPE_YCM = 0x02,
    TARGET_TYPE_NONE = 0x00
  };


  struct CFlag {
    const me::string_view option;
    const me::uint8_t langs;
    CFlag(const me::string_view &option, me::uint8_t langs)
      : option(option), langs(langs)
    {
    }
  };

  struct LFlag {
    const me::string_view option;
    LFlag(const me::string_view &option)
      : option(option)
    {
    }
  };

  struct Library {
    const me::string_view name;
    const LibraryType type;
    Library(const me::string_view &name, LibraryType type)
      : name(name), type(type)
    {
    }
  };

  struct Package {
    const me::string_view name;
    const me::vector<me::string_view> cflags;
    const me::vector<me::string_view> lflags;
    Package(const me::string_view &name, const me::vector<me::string_view> &cflags, const me::vector<me::string_view> &lflags)
      : name(name), cflags(cflags), lflags(lflags)
    {
    }
  };

  struct File {
    const me::string_view path;
    const me::vector<me::string_view> cflags;
    const Lang lang;
    File(const me::string_view &path, const me::vector<me::string_view> &cflags, Lang lang)
      : path(path), cflags(cflags), lang(lang)
    {
    }
  };

  struct Extern {
    const me::string_view path;
    const me::string_view output;
    const me::vector<me::string_view> flags;
    const ExternType type;
    Extern(const me::string_view &path, const me::string_view &output, const me::vector<me::string_view> &flags, ExternType type)
      : path(path), output(output), flags(flags), type(type)
    {
    }
  };

  struct Install {
    const me::string_view src;
    const me::string_view dest;
    Install(const me::string_view &src, const me::string_view &dest)
      : src(src), dest(dest)
    {
    }
  };

  struct ProjectVar : public TableVar {

    static constexpr const char* VARIABLE_NAME = "PROJECT";

    me::string_view name;
    me::string_view version;
    me::string_view output;
    me::string_view build;
    Lang lang;
    Kind kind;
    CC cc;
    me::vector<CFlag> cflags;
    me::vector<LFlag> lflags;
    me::vector<me::string_view> include_directories;
    me::vector<me::string_view> library_directories;
    me::vector<Library> libraries;
    me::vector<Package> packages;
    me::vector<File> files;
    me::vector<Extern> externs;
    me::vector<Install> installs;

    ProjectVar()
      : TableVar(TableVar::Value())
    {
    }

    static constexpr const char* DEFAULT_VERSION = "0.0.1";
    static constexpr Lang DEFAULT_LANG = LANG_C;
    static constexpr Kind DEFAULT_KIND = KIND_EXECUTABLE;
    static constexpr CC DEFAULT_CC = CC_LLVM;
    static constexpr const char* DEFAULT_BUILD_DIR = "./build";

  };

  static inline Lang lang_from_string(const me::string_view &str)
  {
    if (str == "C")
      return LANG_C;
    else if (str == "C++" || str == "CPP" || str == "CXX")
      return LANG_CXX;
    else if (str == "OBJC" || str == "OBJ_C" || str == "OBJECTIVE_C")
      return LANG_OBJC;
    char temp[str.size() + 1];
    throw RuntimeException(Text::Eunknown_language, str.c_str(temp));
  }

  static inline Kind kind_from_string(const me::string_view &str)
  {
    if (str == "EXECUTABLE")
      return KIND_EXECUTABLE;
    else if (str == "STATIC_LIBRARY")
      return KIND_STATIC_LIBRARY;
    else if (str == "SHARED_LIBRARY")
      return KIND_SHARED_LIBRARY;
    char temp[str.size() + 1];
    throw RuntimeException(Text::Eunknown_kind, str.c_str(temp));
  }

  static inline CC cc_from_string(const me::string_view &str)
  {
    if (str == "GNU")
      return CC_GNU;
    else if (str == "LLVM")
      return CC_LLVM;
    char temp[str.size() + 1];
    throw RuntimeException(Text::Eunknown_compiler, str.c_str(temp));
  }
  
  static inline LibraryType library_type_from_string(const me::string_view &str)
  {
    if (str == "STATIC")
      return LIBRARY_TYPE_STATIC;
    else if (str == "SHARED")
      return LIBRARY_TYPE_SHARED;
    char temp[str.size() + 1];
    throw RuntimeException(Text::Eunknown_library, str.c_str(temp));
  }

  static inline ExternType extern_type_from_string(const me::string_view &str)
  {
    if (str == "CMAKE")
      return EXTERN_TYPE_CMAKE;
    else if (str == "GMAKE")
      return EXTERN_TYPE_GMAKE;
    else if (str == "PREMAKE")
      return EXTERN_TYPE_PREMAKE;
    else if (str == "MESON")
      return EXTERN_TYPE_MESON;
    else if (str == "NINJA")
      return EXTERN_TYPE_NINJA;
    else if (str == "MAKEIT")
      return EXTERN_TYPE_MAKEIT;
    char temp[str.size() + 1];
    throw RuntimeException(Text::Eunknown_external, str.c_str(temp));
  }

  static inline TargetType target_type_from_string(const me::string_view &str)
  {
    if (str == "GMAKE")
      return TARGET_TYPE_GMAKE;
    else if (str == "YCM")
      return TARGET_TYPE_YCM;
    char temp[str.size() + 1];
    throw RuntimeException(Text::Eunknown_target, str.c_str(temp));
  }

  static inline bool target_is_main(TargetType type)
  {
    switch (type)
    {
      case TARGET_TYPE_GMAKE:
	return true;

      default:
	return false;
    }
  }

  static const char* get_cc_name(CC cc, Lang lang)
  {
    switch (cc)
    {
      case CC_LLVM:

	switch (lang)
	{
	  case LANG_CXX:
	    return "clang++";

	  case LANG_C:
	  default:
	    return "clang";
	}
	break;

      case CC_GNU:
      default:

	switch (lang)
	{
	  case LANG_CXX:
	    return "g++";

	  case LANG_C:
	  default:
	  return "gcc";
	}
	break;
    }
  }

  static const me::vector<me::string_view> get_valid_kind_string()
  {
    return {
      "EXECUTABLE", "STATIC_LIBRARY", "SHARED_LIBRARY"
    };
  }

  static const me::vector<me::string_view> get_valid_lang_string()
  {
    return {
      "C", "CPP", "CXX", "OBJC"
    };
  }

  static const me::vector<me::string_view> get_valid_cc_string()
  {
    return {
      "GNU", "LLVM"
    };
  }

  static const me::vector<me::string_view> get_valid_library_string()
  {
    return {
      "STATIC", "SHARED"
    };
  }

  static const me::vector<me::string_view> get_valid_extern_string()
  {
    return {
      "CMAKE", "GMAKE", "PREMAKE", "MESON", "NINJA", "MAKEIT"
    };
  }

  static const me::vector<me::string_view> get_valid_target_string()
  {
    return {
      "GMAKE", "YCM"
    };
  }

}

#endif
