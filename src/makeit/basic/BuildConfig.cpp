#include "makeit/basic/BuildConfig.hpp"
#include "makeit/Common.hpp"

/* ---------- */
/* Link stuff */
/* ---------- */
void makeit::Linker::write(me::string &buffer) const
{
  buffer.append(directory);
  if (!directory.is_empty() && !directory.ends_with("/"))
    buffer.append('/');
  buffer.append(name);
}

void makeit::Library::write(me::string &buffer, const Linker &linker) const
{
  buffer.append("-l").append(name);
}

void makeit::LibraryPath::write(me::string &buffer, const Linker &linker) const
{
  buffer.append("-L").append(path);
}

void makeit::LinkConfig::write(me::string &buffer, const Builder &builder) const
{
  for (const me::string_view &opt : options)
    buffer.append(' ').append(opt);

  for (const Library &lib : libraries)
  {
    buffer.append(' ');
    lib.write(buffer, linker);
  }

  for (const LibraryPath &dir : library_paths)
  {
    buffer.append(' ');
    dir.write(buffer, linker);
  }
}
/* end 'Link stuff' */


/* ------------- */
/* Compile stuff */
/* ------------- */
void makeit::Compiler::write(me::string &buffer) const
{
  buffer.append(directory);
  if (!directory.is_empty() && !directory.ends_with("/"))
    buffer.append('/');
  buffer.append(name);
}

void makeit::Include::write(me::string &buffer, const Compiler &compiler) const
{
  buffer.append("--include=").append(path);
}

void makeit::IncludePath::write(me::string &buffer, const Compiler &compiler) const
{
  buffer.append("-I").append(path);
}

void makeit::CompileConfig::write(me::string &buffer, const Builder &builder) const
{
  for (const me::string_view &opt : options)
    buffer.append(' ').append(opt);

  for (const Include &inc : includes)
  {
    buffer.append(' ');
    inc.write(buffer, compiler);
  }

  for (const IncludePath &dir : include_paths)
  {
    buffer.append(' ');
    dir.write(buffer, compiler);
  }
}
/* end 'Compile stuff' */


/* ----------- */
/* Build stuff */
/* ----------- */
void makeit::Builder::write(me::string &buffer) const
{
  
}

void makeit::Warnings::write(me::string &buffer, const Builder &builder) const
{
}

void makeit::SystemRoot::write(me::string &buffer, const Builder &builder) const
{
  buffer.append("-sysroot=").append(path);
}

void makeit::TargetArch::write(me::string &buffer, const Builder &builder) const
{
}

void makeit::Package::write(me::string &buffer, const Builder &builder) const
{
}

void makeit::BuildConfig::write(me::string &buffer) const
{
  for (const me::string_view &opt : options)
    buffer.append(' ').append(opt);

  warnings.write(buffer, builder);
  buffer.append(' ');

  system_root.write(buffer, builder);
  buffer.append(' ');

  target_arch.write(buffer, builder);
  buffer.append(' ');

  for (const Package &pkg : packages)
  {
    buffer.append(' ');
    pkg.write(buffer, builder);
  }
}

void makeit::BuildConfig::validate()
{
  /* Default C compiler */
  if (builder.compile_config.lang_c.compiler.name.is_empty())
    builder.compile_config.lang_c.compiler.name = identify_compiler_name(config.compiler, LANGUAGE_C);

  /* Default C++ compiler */
  if (builder.compile_config.lang_cxx.compiler.name.is_empty())
    builder.compile_config.lang_cxx.compiler.name = identify_compiler_name(config.compiler, LANGUAGE_CXX);

  /* Default Objective C compiler */
  if (builder.compile_config.lang_objc.compiler.name.is_empty())
    builder.compile_config.lang_objc.compiler.name = identify_compiler_name(config.compiler, LANGUAGE_OBJECTIVE_C);

  /* Default linker */
  if (builder.link_config.linker.name.is_empty())
    builder.link_config.linker.name = identify_linker_name(config.linker, builder.lang);

  /* Default build directory */
  if (builder.directory.is_empty())
    builder.directory = config.build_path;

  if (builder.output.is_empty())
    builder.output = "a.out";
}
/* end 'Build stuff' */


/* ---------------- */
/* static functions */
/* ---------------- */
makeit::Language makeit::language_from_string(const me::string_view &str)
{
  static const me::vector<me::string_view> valid_c = {
    "C", "H"
  };
  static const me::vector<me::string_view> valid_cxx = {
    "CPP", "CXX", "CC", "C++", "HPP", "HXX", "HH", "H++"
  };
  static const me::vector<me::string_view> valid_objc = {
    "IDK"
  };

  if (valid_c.contains(str))
    return LANGUAGE_C;

  if (valid_cxx.contains(str))
    return LANGUAGE_CXX;

  if (valid_objc.contains(str))
    return LANGUAGE_OBJECTIVE_C;

  if (str == "ALL")
    return LANGUAGE_ALL;
  
  char temp[str.size() + 1];
  throw RuntimeException("invalid language '%s'", str.c_str(temp));
}

makeit::Kind makeit::kind_from_string(const me::string_view &str)
{
  if (str == "EXECUTABLE")
    return KIND_EXECUTABLE;

  if (str == "STATIC_LIBRARY")
    return KIND_STATIC_LIBRARY;

  if (str == "SHARED_LIBRARY")
    return KIND_SHARED_LIBRARY;

  char temp[str.size() + 1];
  throw RuntimeException("invalid kind '%s'", str.c_str(temp));
}

me::string_view makeit::identify_compiler_name(const me::string_view &name, Language lang)
{
  if (name.equals_ignore_case("LLVM"))
  {
    switch (lang)
    {
      case LANGUAGE_CXX: return "clang++";
      case LANGUAGE_OBJECTIVE_C: return "clang";
      case LANGUAGE_C:
      default:
	return "clang";
    }
  }else if (name.equals_ignore_case("GNU"))
  {
    switch (lang)
    {
      case LANGUAGE_CXX: return "g++";
      case LANGUAGE_OBJECTIVE_C: return "gcc";
      case LANGUAGE_C:
      default:
	return "gcc";
    }
  }else if (name.equals_ignore_case("clang"))
  {
    switch (lang)
    {
      case LANGUAGE_CXX: return "clang++";
      default: return "clang";
    }
  }else if (name.equals_ignore_case("clang++"))
  {
    switch (lang)
    {
      case LANGUAGE_C: return "clang";
      case LANGUAGE_OBJECTIVE_C: return "clang";
      default: return "clang++";
    }
  }else if (name.equals_ignore_case("gcc"))
  {
    switch (lang)
    {
      case LANGUAGE_CXX: return "g++";
      default: return "gcc";
    }
  }else if (name.equals_ignore_case("g++"))
  {
    switch (lang)
    {
      case LANGUAGE_C: return "gcc";
      case LANGUAGE_OBJECTIVE_C: return "gcc";
      default: return "g++";
    }
  }

  char temp[name.size() + 1];
  throw RuntimeException("invalid compiler name '%s'", name.c_str(temp));
}

me::string_view makeit::identify_linker_name(const me::string_view &name, Language lang)
{
  try {
    return makeit::identify_compiler_name(name, lang);
  }catch (const RuntimeException &unused) { }

  if (name.equals_ignore_case("LD"))
  {
    return "ld";
  }

  char temp[name.size() + 1];
  throw RuntimeException("invalid linker name '%s'", name.c_str(temp));
}
/* static functions end */
