#include "makeit/target/YCMTarget.hpp"

#include <libme/filesystem.hpp>

static void append_array(me::string* output, const me::vector<me::string_view> &arr);

int makeit::YCMTarget::generate(const ProjectVar &project)
{
  write_cflags(project);
  output->push_back('\n');

  write_files(project);
  output->push_back('\n');

  output->append("def Settings(**kwargs):\n");
  output->append("\tkey = kwargs['filename']\n");
  output->append("\tif key in SOURCES:\n");
  output->append("\t\treturn { 'flags': SOURCES[key] }\n");
  output->append("\telse:\n");
  output->append("\t\tif IsCFile(key):\n");
  output->append("\t\t\treturn { 'flags': C_CFLAGS }\n");
  output->append("\t\telif IsCXXFile(key):\n");
  output->append("\t\t\treturn { 'flags': CXX_CFLAGS }\n");
  output->append("\t\telif IsOBJCFile(key):\n");
  output->append("\t\t\treturn { 'flags': OBJC_CFLAGS }\n");
  output->append("\treturn { 'flags': [ ] }\n\n");

  output->append("def IsCXXFile(file):\n");
  output->append("\tCXX_FILES = ['.cpp', '.cxx', '.cc', '.hpp', '.hxx', '.hh']\n");
  output->append("\tfor ext in CXX_FILES:\n");
  output->append("\t\tif file.endswith(ext):\n");
  output->append("\t\t\treturn True\n");
  output->append("\treturn False\n\n");

  output->append("def IsCFile(file):\n");
  output->append("\tC_FILES = ['.c', '.h']\n");
  output->append("\tfor ext in C_FILES:\n");
  output->append("\t\tif file.endswith(ext):\n");
  output->append("\t\t\treturn True\n");
  output->append("\treturn False\n\n");

  output->append("def IsOBJCFile(file):\n");
  output->append("\tOBJC_FILES = ['.h', '.m', '.mm', '.M']\n");
  output->append("\tfor ext in OBJC_FILES:\n");
  output->append("\t\tif file.endswith(ext):\n");
  output->append("\t\t\treturn True\n");
  output->append("\treturn False\n\n");
  return 0;
}

int makeit::YCMTarget::write_cflags(const ProjectVar &project)
{
#define WRITECFLAGS(l) \
  output->append("[ "); \
  for (size_t i = 0; i < project.cflags.size(); i++) \
  { \
    const CFlag &flag = project.cflags.at(i); \
\
    if (!(flag.langs & l)) \
      continue; \
\
    output->push_back('\''); \
    output->append(flag.option); \
    output->push_back('\''); \
\
    if (i != project.cflags.size() - 1) \
      output->append(", "); \
  } \
  output->append(" ]\n");

  output->append("INCD = [ ");
  for (size_t i = 0; i < project.include_directories.size(); i++)
  {
    output->append("'-I").append(project.include_directories.at(i)).push_back('\'');

    if (i != project.include_directories.size() - 1)
      output->append(", ");
  }
  output->append(" ]\n");

  output->append("C_CFLAGS = INCD + ");
  WRITECFLAGS(LANG_C)

  output->append("CXX_CFLAGS = INCD + ");
  WRITECFLAGS(LANG_CXX)

  output->append("OBJC_CFLAGS = INCD + ");
  WRITECFLAGS(LANG_OBJC)
  return 0;
#undef WRITECFLAGS
}

int makeit::YCMTarget::write_files(const ProjectVar &project)
{
  output->append("SOURCES = {\n");
  for (me::size_t i = 0; i < project.files.size(); i++)
  {
    const File &file = project.files.at(i);

    char abs_file_path[PATH_MAX];
    me::filesystem::absolute(file.path, abs_file_path);

    output->append("\t'").append(abs_file_path).append("': ");

    if (file.lang == LANG_C)
      output->append("C_CFLAGS + ");
    else if (file.lang == LANG_CXX)
      output->append("CXX_CFLAGS + ");
    else if (file.lang == LANG_OBJC)
      output->append("OBJC_CFLAGS + ");

    append_array(output, file.cflags);

    if (i != project.files.size() - 1)
      output->append(",\n");
    else
      output->append("\n");
  }
  output->append("}\n");


  return 0;
}

void append_array(me::string* output, const me::vector<me::string_view> &arr)
{
  output->append("[ ");

  for (size_t i = 0; i < arr.size(); i++)
  {
    output->push_back('\'');
    output->append(arr.at(i));
    output->push_back('\'');

    if (i != arr.size() - 1)
      output->append(", ");
  }

  output->append(" ]");
}
