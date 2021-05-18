#include "makeit/target/YCMTarget.hpp"

#include <libme/filesystem.hpp>

int makeit::ycm::generate(const Project &project, me::string &buffer)
{
  //bool comments = true;

  ///* -------------- */
  ///* Compiler flags */
  ///* -------------- */
  //{
  //  if (comments)
  //    buffer.append("# Compiler flags for language C\n");
  //  buffer.append("CFLAGS_C = [\n");
  //  const me::vector<Option> &options_c = project.build_config.compile_options.lang_c;
  //  if (options_c.size() != 0)
  //  {
  //    buffer.append("\t'");
  //    options_c.at(0).string_write(buffer);
  //    buffer.append("'");
  //    for (me::size_t i = 1; i != options_c.size(); i++)
  //    {
  //      buffer.append(",\n\t'");
  //      options_c.at(i).string_write(buffer);
  //      buffer.append("'");
  //    }
  //  }
  //  buffer.append("]\n\n");

  //  if (comments)
  //    buffer.append("# Compiler flags for language C++\n");
  //  buffer.append("CFLAGS_CXX = [\n");
  //  const me::vector<Option> &options_cxx = project.build_config.compile_options.lang_cxx;
  //  if (options_cxx.size() != 0)
  //  {
  //    buffer.append("\t'");
  //    options_cxx.at(0).string_write(buffer);
  //    buffer.append("'");
  //    for (me::size_t i = 1; i != options_cxx.size(); i++)
  //    {
  //      buffer.append(",\n\t'");
  //      options_cxx.at(i).string_write(buffer);
  //      buffer.append("'");
  //    }
  //  }
  //  buffer.append("]\n\n");

  //  if (comments)
  //    buffer.append("# Compiler flags for language Objective C\n");
  //  const me::vector<Option> &options_objc = project.build_config.compile_options.lang_objc;
  //  buffer.append("CFLAGS_OBJC = [\n");
  //  if (options_objc.size() != 0)
  //  {
  //    buffer.append("\t'");
  //    options_objc.at(0).string_write(buffer);
  //    buffer.append("'");
  //    for (me::size_t i = 1; i != options_objc.size(); i++)
  //    {
  //      buffer.append(",\n\t'");
  //      options_objc.at(i).string_write(buffer);
  //      buffer.append("'");
  //    }
  //  }
  //  buffer.append("]\n\n");
  //}


  ///* ------------ */
  ///* Source files */
  ///* ------------ */
  //{
  //  static const auto write_source = [](me::string &buffer, const Source &source) {
  //    buffer.append("\t'");
  //    char abs_path[PATH_MAX];
  //    me::filesystem::absolute(source.source, abs_path);
  //    buffer.append(abs_path).append("':");

  //    if (source.language == LANGUAGE_C)
  //      buffer.append(" CFLAGS_C");
  //    else if (source.language == LANGUAGE_CXX)
  //      buffer.append(" CFLAGS_CXX");
  //    else if (source.language == LANGUAGE_OBJECTIVE_C)
  //      buffer.append(" CFLAGS_OBJC");

  //    if (source.options.size() != 0)
  //    {
  //      buffer.append(" + ['");
  //      source.options.at(0).string_write(buffer);
  //      buffer.append('\'');

  //      for (me::size_t i = 1; i != source.options.size(); i++)
  //      {
  //        buffer.append(", '");
  //        source.options.at(i).string_write(buffer);
  //        buffer.append('\'');
  //      }
  //      buffer.append(']');
  //    }
  //  };

  //  buffer.append("SOURCES = {\n");
  //  if (project.sources.size() != 0)
  //  {
  //    write_source(buffer, project.sources.at(0));

  //    for (me::size_t i = 1; i != project.sources.size(); i++)
  //    {
  //      buffer.append(",\n");
  //      write_source(buffer, project.sources.at(i));
  //    }
  //    buffer.append("\n}\n\n");
  //  }
  //}

  //buffer.append("def Settings(**kwargs):\n");
  //buffer.append("\tkey = kwargs['filename']\n");
  //buffer.append("\tif key in SOURCES:\n");
  //buffer.append("\t\treturn { 'flags': SOURCES[key] }\n");
  //buffer.append("\telse:\n");
  //buffer.append("\t\tif IsCFile(key):\n");
  //buffer.append("\t\t\treturn { 'flags': CFLAGS_C }\n");
  //buffer.append("\t\telif IsCXXFile(key):\n");
  //buffer.append("\t\t\treturn { 'flags': CFLAGS_CXX }\n");
  //buffer.append("\t\telif IsOBJCFile(key):\n");
  //buffer.append("\t\t\treturn { 'flags': CFLAGS_OBJ }\n");
  //buffer.append("\treturn { 'flags': [ ] }\n\n");

  //buffer.append("def IsCXXFile(file):\n");
  //buffer.append("\tCXX_FILES = ['.cpp', '.cxx', '.cc', '.hpp', '.hxx', '.hh']\n");
  //buffer.append("\tfor ext in CXX_FILES:\n");
  //buffer.append("\t\tif file.endswith(ext):\n");
  //buffer.append("\t\t\treturn True\n");
  //buffer.append("\treturn False\n\n");

  //buffer.append("def IsCFile(file):\n");
  //buffer.append("\tC_FILES = ['.c', '.h']\n");
  //buffer.append("\tfor ext in C_FILES:\n");
  //buffer.append("\t\tif file.endswith(ext):\n");
  //buffer.append("\t\t\treturn True\n");
  //buffer.append("\treturn False\n\n");

  //buffer.append("def IsOBJCFile(file):\n");
  //buffer.append("\tOBJC_FILES = ['.h', '.m', '.mm', '.M']\n");
  //buffer.append("\tfor ext in OBJC_FILES:\n");
  //buffer.append("\t\tif file.endswith(ext):\n");
  //buffer.append("\t\t\treturn True\n");
  //buffer.append("\treturn False\n\n");
  return 0;
}
