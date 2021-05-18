#include "makeit/target/GMakeTarget.hpp"
#include "makeit/Text.hpp"

int makeit::gmake::generate(const Project &project, me::string &buffer)
{
  bool comments = true;

  buffer.append("NAME = ").append(project.name).append("_").append(project.version) += '\n';
  buffer.append("VERSION = ").append(project.version) += '\n';

  buffer.append("OUTPUT = ").append(project.build_config.builder.output) += '\n';

  if (comments)
    buffer.append("\n# Directory for the object files\n");
  buffer.append("BUILD = ").append(project.build_config.builder.directory) += '\n';

  if (comments)
    buffer.append("\n# Compiler for the language C\n");
  buffer.append("CC = ");
  project.build_config.builder.compile_config.lang_c.compiler.write(buffer);
  buffer.append('\n');

  if (comments)
    buffer.append("\n# Compiler for the language C++\n");
  buffer.append("CXXC = ");
  project.build_config.builder.compile_config.lang_cxx.compiler.write(buffer);
  buffer.append('\n');

  if (comments)
    buffer.append("\n# Compiler for the language Objective C\n");
  buffer.append("OBJCC = ");
  project.build_config.builder.compile_config.lang_objc.compiler.write(buffer);
  buffer.append('\n');

  if (comments)
    buffer.append("\n# Linker\n");
  buffer.append("LINKER = ");
  project.build_config.builder.link_config.linker.write(buffer);
  buffer.append('\n');



  /* --------------- */
  /* Options / Flags */
  /* --------------- */
  {
    if (comments)
      buffer.append("\n# Compiler flags for language C\n");
    buffer.append("CFLAGS =");
    project.build_config.builder.compile_config.lang_c.write(buffer, project.build_config.builder);
    buffer += '\n';

    if (comments)
      buffer.append("\n# Compiler flags for language C++\n");
    buffer.append("CXXFLAGS =");
    project.build_config.builder.compile_config.lang_cxx.write(buffer, project.build_config.builder);
    buffer += '\n';

    if (comments)
      buffer.append("\n# Compiler flags for language Objective C\n");
    buffer.append("OBJCFLAGS =");
    project.build_config.builder.compile_config.lang_objc.write(buffer, project.build_config.builder);
    buffer += '\n';

    if (comments)
      buffer.append("\n# Linker flags\n");
    buffer.append("LFLAGS =");
    project.build_config.builder.link_config.write(buffer, project.build_config.builder);
    buffer += '\n';
    buffer += '\n';
  }


  /* ------------ */
  /* Source files */
  /* ------------ */
  {
    buffer.append("SOURCES =");
    for (const Source &source : project.sources)
    {
      buffer.append(" \\\n\t");
      source.string_write(buffer);
    }

    buffer.append("\nOBJECTS = $(SOURCES:%=$(BUILD)/%.o)\n");
    buffer.append("DEPENDS = $(SOURCES:%=$(BUILD)/%.d)\n");

    buffer += '\n';
  }


  /* --------- */
  /* Externals */
  /* --------- */
  {
    buffer.append("EXTERNALS =");
    for (const External &external : project.externals)
    {
      buffer.append(" \\\n\t");
      buffer.append(external.output);
    }
    buffer += '\n';
    buffer += '\n';
  }

  /* --------- */
  /* Main rule */
  /* --------- */
  {
    buffer.append(".PHONY: $(NAME)\n");
    buffer.append("$(NAME): $(OUTPUT) $(EXTERNALS)\n");
    buffer += '\n';
  }

  
  /* --------- */
  /* Link rule */
  /* --------- */
  {
    buffer.append("$(OUTPUT): $(OBJECTS)\n");
    buffer.append("\t$(LINKER) -o $@ $^ $(LFLAGS)\n");
    buffer += '\n';
  }


  buffer.append("-include $(DEPENDS)\n\n");


  /* ------------ */
  /* Source rules */
  /* ------------ */
  {
    for (const Source &source : project.sources)
    {
      source.string_write("$(BUILD)", buffer).append(": ");
      source.string_write(buffer).append("\n\t");

      if (source.language == LANGUAGE_C)
	buffer.append("$(CC) $(CFLAGS)");
      else if (source.language == LANGUAGE_CXX)
	buffer.append("$(CXXC) $(CXXFLAGS)");
      else if (source.language == LANGUAGE_OBJECTIVE_C)
	buffer.append("$(OBJCC) $(OBJCFLAGS)");

      buffer.append(" -c -o $@ $<");
      source.config.write(buffer, project.build_config.builder);
      buffer.append(" -MMD\n\n");
    }
  }


  /* -------------- */
  /* External rules */
  /* -------------- */
  {
    for (const External &external : project.externals)
    {
      buffer.append(external.output).append(":\n");
      buffer.append('\t').append(external.command);

      for (const me::string_view &option : external.options)
      {
	buffer.append(' ').append(option);
      }
      buffer.append("\n\n");
    }
  }


  /* ----------------- */
  /* Installation rule */
  /* ----------------- */
  {
    buffer.append(".PHONY: install\n");
    buffer.append("install:\n");
    for (const Installation &installation : project.installations)
    {
      buffer.append("\tinstall ");
      buffer.append(installation.source).append(' ');
      buffer.append(installation.directory).append('\n');
    }
    buffer.append('\n');
  }


  /* ---------- */
  /* Clean rule */
  /* ---------- */
  {
    buffer.append(".PHONY: clean\n");
    buffer.append("clean:\n");
    buffer.append("\trm -rf $(OBJECTS) $(DEPENDS)\n");
  }
  return 0;
}
