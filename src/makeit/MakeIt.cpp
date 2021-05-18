#include "makeit/MakeIt.hpp"
#include "makeit/Config.hpp"
#include "makeit/Common.hpp"
#include "makeit/basic/Function.hpp"
#include "makeit/Logger.hpp"
#include "makeit/Text.hpp"
#include "makeit/lexer/Lexer.hpp"
#include "makeit/parser/Parser.hpp"
#include "makeit/target/GMakeTarget.hpp"
#include "makeit/target/YCMTarget.hpp"

/* --- Functions --- */
#include "makeit/functions/FnSetProperty.hpp"
#include "makeit/functions/FnAddProperty.hpp"
#include "makeit/functions/FnAddExtern.hpp"
#include "makeit/functions/FnAddFiles.hpp"
#include "makeit/functions/FnAddInstall.hpp"
#include "makeit/functions/FnConfigure.hpp"
#include "makeit/functions/FnPrint.hpp"
#include "makeit/functions/FnProject.hpp"
#include "makeit/functions/FnSource.hpp"

#include <libme/filesystem.hpp>
#include <libme/options.hpp>

#define MAKEIT_VERSION_STRING "21.2.0"
#define MAKEIT_NAME_STRING "MakeIt"

namespace makeit {
  Config config;
  Instance instance(stdout);
  Project project;
}

makeit::Instance::Instance(FILE* log)
  : logger(log), lexer(logger), parser(logger, alloc, context)
{
}

int makeit::Instance::parse_args(int argc, char** argv)
{
  static struct me::option_info options[] = {
    {1, "help", 'h', me::OPTION_VALUE_NONE},
    {2, "file", 'f', me::OPTION_VALUE_REQUIRED},
    {3, "define", 'D', me::OPTION_VALUE_OPTIONAL},
  };

  me::size_t index = 0;
  while (index != argc)
  {
    const me::option option = me::next_option(3, options, argc, argv, index);

    if (option.info == nullptr)
      continue;

    switch (option.info->short_name)
    {
      case 'h':
	print_usage();
	break;

      case 'f':
	config.source_file = option.value1;
	break;

      case 'D':
	if (!option.value1.is_empty())
	{
	  if (!option.value2.is_empty())
	  {
	    context.variables[option.value1] = alloc.calloc<StringVar>(option.value2);
	  }else
	  {
	    context.variables[option.value1] = alloc.calloc<IntegerVar>(1);
	  }
	}
	break;
    }
  }
  return 0;
}

int makeit::Instance::init(int argc, char** argv)
{
  char config_file_str[PATH_MAX];
  ::strcpy(config_file_str, getenv("HOME"));
  ::strcat(config_file_str, "/.config/makeit/init.mi");

  config.compiler = "LLVM";
  config.linker = "LLVM";
  config.build_path = "./build";
  config.config_file = config_file_str;
  config.source_file = "./MIBuild";

  parse_args(argc, argv);

  try {

    init_variables();
    init_functions();

    /* Read config file */
    if (me::filesystem::exists(config.config_file))
      read_source(config.config_file);

    read_source(config.source_file);

    /* Make sure all necessary values are set. */
    /* If not; assign to default values */
    project.build_config.validate();

    generate_targets();

  }catch (const Exception &e1)
  {
    e1.print(stdout);
  }catch (const RuntimeException &e2)
  {
    logger.error("%s", e2.get_message());
  }
  return 0;
}

int makeit::Instance::init_variables()
{
  file_variable = alloc.calloc<StringVar>("");
  directory_variable = alloc.calloc<StringVar>("");
  main_target_variable = alloc.calloc<StringVar>("GMAKE");
  targets_variable = alloc.calloc<ArrayVar>(ArrayVar::Value());
  gmake_path_variable = alloc.calloc<StringVar>("./Makefile");
  ycm_path_variable = alloc.calloc<StringVar>("./.ycm_extra_conf.py");

  context.variables["FILE"] = file_variable;
  context.variables["DIR"] = directory_variable;
  context.variables[".main_target"] = main_target_variable;
  context.variables[".targets"] = targets_variable;
  context.variables[".gmake_path"] = gmake_path_variable;
  context.variables[".ycm_path"] = ycm_path_variable;

  context.variables["LLVM"] = alloc.calloc<StringVar>("clang");
  context.variables["GNU"] = alloc.calloc<StringVar>("gcc");
  context.variables["LD"] = alloc.calloc<StringVar>("ld");

  static me::vector<me::string_view> enums = {};
  enums.push_back_vector({"EXECUTABLE", "STATIC_LIBRARY", "SHARED_LIBRARY", "STATIC", "SHARED"});
  enums.push_back_vector({"C", "CXX", "CPP", "OBJC"});
  enums.push_back_vector({"GMAKE", "YCM"});
  enums.push_back_vector({"ALL"});

  for (const me::string_view &e : enums)
    context.variables.put(e, alloc.calloc<StringVar>(e));
  return 0;
}

int makeit::Instance::init_functions()
{
  context.register_function(new AddCFlagsFunc());
  context.register_function(new AddLFlagsFunc());
  context.register_function(new AddFlagsFunc());
  context.register_function(new AddIncludeFunc());
  context.register_function(new AddIncludePathFunc());
  context.register_function(new AddLibraryFunc());
  context.register_function(new AddLibraryPathFunc());
  context.register_function(new AddPackageFunc());

  context.register_function(new SetBuildDirectoryFunc());
  context.register_function(new SetBinaryDirectoryFunc());
  context.register_function(new SetOutputFunc());
  context.register_function(new SetLanguageFunc());
  context.register_function(new SetKindFunc());
  context.register_function(new SetCompilerFunc());
  context.register_function(new SetLinkerFunc());
  context.register_function(new SetSystemRootFunc());
  context.register_function(new SetTargetArchFunc());

  context.register_function(new AddExternFunc());
  context.register_function(new AddFilesFunc());
  context.register_function(new AddInstallFunc());
  context.register_function(new ConfigureFunc());
  context.register_function(new PrintFunc());
  context.register_function(new ProjectFunc());
  context.register_function(new SourceFunc());
  return 0;
}

int makeit::Instance::print_usage() const
{
  return 0;
}

int makeit::Instance::print_version() const
{
  return 0;
}

int makeit::Instance::read_source(const me::string_view &path)
{
  /* Saving the old file and directory values */
  const StringVar::Value old_file_value = file_variable->value;
  const StringVar::Value old_directory_value = directory_variable->value;

  if (!me::filesystem::exists(path))
  {
    char temp[path.size() + 1];
    throw RuntimeException("file not found '%s'", path.c_str(temp));
  }

  /* Reading the file */
  me::filesystem::file_status file;
  me::filesystem::status(path, file);
  char* data = new char[file.size + 1];
  read_file(path, file.size, data);
  data[file.size] = '\0';

  /* Getting the directory name of current file path */
  char directory_path[PATH_MAX];
  me::filesystem::directory(path, directory_path);

  /* Setting the current file and directory */
  file_variable->value = path;
  directory_variable->value = directory_path;

  const MakeItSource source = {path, data};

  /* Creating tokens from the text file */
  me::vector<Token> tokens;
  lexer.lexify(source, tokens);

  /* Parsing the tokens and do good stuff */
  parser.parse(tokens.cbegin());

  /* Assigning the old file and directory values */
  file_variable->value = old_file_value;
  directory_variable->value = old_directory_value;
  return 0;
}

int makeit::Instance::generate_targets() const
{
  const StringVar::Value &main_target = main_target_variable->value;
  generate_target(main_target);

  for (const Variable* var : targets_variable->value)
  {
    /* TODO: error stuff */
    generate_target(reinterpret_cast<const StringVar*>(var)->value);
  }
  return 0;
}

int makeit::Instance::generate_target(const me::string_view &target) const
{
  me::string_view file;
  me::string buffer;
  buffer.reserve(4096);

  if (target.equals_ignore_case("gmake"))
  {
    file = gmake_path_variable->value;
    gmake::generate(project, buffer);
  }else if (target.equals_ignore_case("ycm"))
  {
    file = ycm_path_variable->value;
    ycm::generate(project, buffer);
  }

  write_file(file, buffer.size(), buffer.data());
  return 0;
}

int makeit::Instance::read_file(const me::string_view &path, size_t len, char* data) const
{
  char path_cstr[path.size() + 1];
  path.c_str(path_cstr);

  FILE* file = ::fopen(path_cstr, "rb");
  if (!file)
    throw me::exception("failed to open file[%s] for reading", path_cstr);

  ::fread(data, 1, len, file);
  ::fclose(file);
  return 0;
}

int makeit::Instance::write_file(const me::string_view &path, size_t len, char* data) const
{
  char path_cstr[path.size() + 1];
  path.c_str(path_cstr);

  FILE* file = ::fopen(path_cstr, "wb");
  if (!file)
    throw me::exception("failed to open file[%s] for writing", path_cstr);

  ::fwrite(data, 1, len, file);
  ::fclose(file);
  return 0;
}

int main(int argc, char** argv)
{
  try {
    return makeit::instance.init(argc, argv);
  }catch (const me::exception &e)
  {
    printf("catched me::exception: %s\n", e.get_message());
    return 1;
  }
}
