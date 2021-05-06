#include "makeit/target/GMakeTarget.hpp"

#include "makeit/Text.hpp"

static void append_array(me::string* output, const me::vector<me::string_view> &arr);

int makeit::GMakeTarget::generate(const ProjectVar &project)
{
  output->append("NAME = ").append(project.name).append("_").append(project.version) += '\n';
  output->append("VERSION = ").append(project.version) += '\n';
  output->append("CC = ").append(get_cc_name(project.cc, project.lang)) += '\n';
  output->append("BUILD = ").append(project.build) += '\n';
  output->append("OUTPUT = ").append(project.output) += '\n';

  write_cflags(project);
  write_lflags(project);

  write_files(project);
  output->push_back('\n');

  write_externs(project);
  output->push_back('\n');
  
  write_rule_main(project);
  output->push_back('\n');

  write_rule_link(project);
  output->push_back('\n');

  output->append("-include $(DEPS)\n");
  output->push_back('\n');

  write_rule_files(project);
  output->push_back('\n');

  write_rule_externs(project);
  output->push_back('\n');

  write_rule_installs(project);
  output->push_back('\n');

  write_rule_clean(project);
  return 0;
}

int makeit::GMakeTarget::write_cflags(const ProjectVar &project)
{
#define WRITECFLAGS(l) \
  for (size_t i = 0; i < project.cflags.size(); i++) \
  { \
    const CFlag &flag = project.cflags.at(i); \
\
    if (!(flag.langs & l)) \
      continue; \
\
    output->append(flag.option); \
\
    if (i != project.cflags.size() - 1) \
      output->push_back(' '); \
  } \
  output->push_back('\n');

  output->append("INCD = ");
  for (size_t i = 0; i < project.include_directories.size(); i++)
  {
    output->append("-I").append(project.include_directories.at(i));

    if (i != project.include_directories.size() - 1)
      output->push_back(' ');
  }
  output->push_back('\n');

  output->append("LIBD = ");
  for (me::size_t i = 0; i < project.library_directories.size(); i++)
  {
    output->append("-L").append(project.library_directories.at(i));

    if (i != project.library_directories.size() - 1)
      output->push_back(' ');
  }
  output->push_back('\n');

  output->append("LIBS = ");
  for (me::size_t i = 0; i < project.libraries.size(); i++)
  {
    output->append("-l").append(project.libraries.at(i).name);

    if (i != project.libraries.size() - 1)
      output->push_back(' ');
  }
  output->push_back('\n');

  output->append("CFLAGS = $(INCD)\n");

  output->append("C_CFLAGS = $(CFLAGS) ");
  WRITECFLAGS(LANG_C)

  output->append("CXX_CFLAGS = $(CFLAGS) ");
  WRITECFLAGS(LANG_CXX)

  output->append("OBJC_CFLAGS = $(CFLAGS) ");
  WRITECFLAGS(LANG_OBJC)
  return 0;
#undef WRITECFLAGS
}

int makeit::GMakeTarget::write_lflags(const ProjectVar &project)
{
  output->append("LFLAGS = $(LIBD) $(LIBS) ");

  for (me::size_t i = 0; i < project.lflags.size(); i++)
  {
    const LFlag &flag = project.lflags.at(i);

    output->append(flag.option);

    if (i != project.cflags.size() - 1)
      output->push_back(' ');
  }
  output->push_back('\n');
  return 0;
}

int makeit::GMakeTarget::write_files(const ProjectVar &project)
{
  output->append("SRCS = ");
  for (size_t i = 0; i < project.files.size(); i++)
  {
    output->append(project.files.at(i).path);

    if (i != project.files.size() - 1)
      output->append(" \\\n\t");
  }
  output->append("\nOBJS = $(SRCS:%=$(BUILD)/%.o)\n");
  output->append("DEPS = $(OBJS:%.o=%.d)\n");
  return 0;
}

int makeit::GMakeTarget::write_externs(const ProjectVar &project)
{
  output->append("EXTS = ");
  for (size_t i = 0; i < project.externs.size(); i++)
  {
    output->append(project.externs.at(i).output);

    if (i != project.externs.size() - 1)
      output->append(" \\\n\t");
  }

  output->push_back('\n');
  return 0;
}

int makeit::GMakeTarget::write_rule_main(const ProjectVar &project)
{
  output->append(".PHONY: $(NAME)\n");
  output->append("$(NAME): $(OUTPUT) $(EXTS)\n");
  return 0;
}

int makeit::GMakeTarget::write_rule_link(const ProjectVar &project)
{
  output->append("$(OUTPUT): $(OBJS)\n");

  if (project.kind == KIND_EXECUTABLE)
    output->append("\t@$(CC) -o $@ $^ $(LFLAGS)\n");
  else if (project.kind == KIND_SHARED_LIBRARY)
    output->append("\t@$(CC) -o $@ -shared $^ $(LFLAGS)\n");
  else if (project.kind == KIND_STATIC_LIBRARY)
    output->append("\t@ar rcs $@ $^\n");
  return 0;
}

int makeit::GMakeTarget::write_rule_files(const ProjectVar &project)
{
  for (const File &file : project.files)
  {
    output->append("$(BUILD)/").append(file.path).append(".o: ").append(file.path) += '\n';
    output->append("\t@echo \"").append(Text::Scompile_source).append("\"\n");
    output->append("\t@mkdir -p $(dir $@)") += '\n';
    output->append("\t@$(CC) -c -o $@ $< ");

    if (file.lang == LANG_CXX)
      output->append("$(CXX_CFLAGS)");
    else if (file.lang == LANG_C)
      output->append("$(C_CFLAGS)");
    else if (file.lang == LANG_OBJC)
      output->append("$(OBJC_CFLAGS)");

    append_array(output, file.cflags);

    output->append(" -MMD\n\n");
  }
  return 0;
}

int makeit::GMakeTarget::write_rule_externs(const ProjectVar &project)
{
  for (const Extern &ext : project.externs)
  {
    output->append(ext.output).append(": ").append(ext.path).append("\n\t");

    if (ext.type == EXTERN_TYPE_CMAKE)
      output->append("cmake $< ");
    else if (ext.type == EXTERN_TYPE_GMAKE)
      output->append("make -f $< ");
    else if (ext.type == EXTERN_TYPE_MAKEIT)
      output->append("makeit -f $< ");

    append_array(output, ext.flags);

    output->append("\n\n");
  }
  return 0;
}

int makeit::GMakeTarget::write_rule_installs(const ProjectVar &project)
{
  output->append(".PHONY: install\n");
  output->append("install:\n");

  for (const Install &inst : project.installs)
  {
    output->append("\tcp ").append(inst.src).push_back(' ');
    output->append(inst.dest).push_back('\n');
  }
  return 0;
}

int makeit::GMakeTarget::write_rule_clean(const ProjectVar &project)
{
  output->append(".PHONY: clean\n");
  output->append("clean:\n");
  output->append("\trm -f $(OUT) $(OBJS) $(DEPS)\n");
  return 0;
}

void append_array(me::string* output, const me::vector<me::string_view> &arr)
{
  for (me::size_t i = 0; i < arr.size(); i++)
  {
    output->append(arr.at(i));

    if (i != arr.size() - 1)
      output->push_back(' ');
  }
}
