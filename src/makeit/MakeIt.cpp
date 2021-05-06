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
#include "makeit/functions/FnAddCFlags.hpp"
#include "makeit/functions/FnAddDefine.hpp"
#include "makeit/functions/FnAddInclude.hpp"
#include "makeit/functions/FnAddIncludeDir.hpp"
#include "makeit/functions/FnAddLFlags.hpp"
#include "makeit/functions/FnAddLibrary.hpp"
#include "makeit/functions/FnAddLibraryDir.hpp"
#include "makeit/functions/FnAddPackage.hpp"
#include "makeit/functions/FnExtern.hpp"
#include "makeit/functions/FnFiles.hpp"
#include "makeit/functions/FnInstall.hpp"
#include "makeit/functions/FnPrint.hpp"
#include "makeit/functions/FnProject.hpp"
#include "makeit/functions/FnSource.hpp"

#include <libme/filesystem.hpp>

#include <getopt.h>

#define MAKEIT_VERSION_STRING "21.2.0"
#define MAKEIT_NAME_STRING "MakeIt"

makeit::Instance::Instance(FILE* log)
  : logger(log), context({.func_user_ptr = this}), lexer(logger), parser(logger, alloc, context)
{
}

int makeit::Instance::parse_args(int argc, char** argv)
{
  static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"file", required_argument, 0, 'f'},

    {"define", required_argument, 0, 'D'}
  };

  while (true)
  {
    int opt_index;
    int c = getopt_long(argc, argv, "hf:D::", long_options, &opt_index);

    if (c == -1)
      break;

    switch (c)
    {
      case 'h':
	print_usage();
	break;

      case 'f':
	config.source_file = optarg;
	break;

      case 'D':
	if (optarg)
	  context.variables[optarg] = alloc.calloc<IntegerVar>(1);
	break;
    }
  }
  return 0;
}

int makeit::Instance::init(int argc, char** argv)
{
  config.config_file = getenv("HOME");
  config.config_file += "/.config/makeit/init.mi";
  config.source_file = "./MIBuild";

  parse_args(argc, argv);

  init_variables();
  init_functions();

  try {

    /* Read config file */
    if (me::filesystem::exists(config.config_file))
      read_source(config.config_file);

    read_source(config.source_file);

    /* Generating targets */
    const TargetType main_target = target_type_from_string(main_target_variable->value);
    generate_target(main_target);
    for (me::size_t i = 0; i < targets_variable->value.size(); i++)
    {
      /* TODO: error stuff */
      Variable* target_var = targets_variable->value.at(i);
      const TargetType target = target_type_from_string(reinterpret_cast<TextVar*>(target_var)->value);
      if (target != main_target)
	generate_target(target);
    }

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
  file_variable = alloc.calloc<TextVar>("");
  directory_variable = alloc.calloc<TextVar>("");
  main_target_variable = alloc.calloc<TextVar>("GMAKE");
  targets_variable = alloc.calloc<ArrayVar>(ArrayVar::Value());
  gmake_path_variable = alloc.calloc<TextVar>("./Makefile");
  ycm_path_variable = alloc.calloc<TextVar>("./.ycm_extra_conf.py");

  context.variables["FILE"] = file_variable;
  context.variables["DIR"] = directory_variable;
  context.variables[".main_target"] = main_target_variable;
  context.variables[".targets"] = targets_variable;
  context.variables[".gmake_path"] = gmake_path_variable;
  context.variables[".ycm_path"] = ycm_path_variable;

  project_var.cflags.emplace_back("-xc", LANG_C);
  project_var.cflags.emplace_back("-xc++", LANG_CXX);
  project_var.cflags.emplace_back("-xobjc", LANG_OBJC);
  context.variables[ProjectVar::VARIABLE_NAME] = &project_var;

  static me::vector<me::string_view> enums = {};
  enums.push_back_vector(get_valid_kind_string());
  enums.push_back_vector(get_valid_lang_string());
  enums.push_back_vector(get_valid_cc_string());
  enums.push_back_vector(get_valid_library_string());
  enums.push_back_vector(get_valid_extern_string());
  enums.push_back_vector(get_valid_target_string());

  for (const me::string_view &e : enums)
    context.variables.put(e, alloc.calloc<TextVar>(e));
  return 0;
}

int makeit::Instance::init_functions()
{
  func_add_cflags_init(context);
  func_add_define_init(context);
  func_add_include_init(context);
  func_add_include_directory_init(context);
  func_add_lflags_init(context);
  func_add_library_init(context);
  func_add_library_directory_init(context);
  func_add_package_init(context);
  func_extern_init(context);
  func_files_init(context);
  func_install_init(context);
  func_print_init(context);
  func_project_init(context);
  func_source_init(context);
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
  const me::string_view old_file_value = file_variable->value;
  const me::string_view old_directory_value = directory_variable->value;

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

  const Source source = {path, {data, file.size}};

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

int makeit::Instance::generate_target(TargetType target) const
{
  switch (target)
  {
    case TARGET_TYPE_GMAKE:
      {
	me::string file_data;
	GMakeTarget gmake(&file_data);
	gmake.generate(project_var);
	write_file(gmake_path_variable->value, file_data.size(), file_data.data());
      }
      break;

    case TARGET_TYPE_YCM:
      {
	me::string file_data;
	YCMTarget ycm(&file_data);
	ycm.generate(project_var);
	write_file(ycm_path_variable->value, file_data.size(), file_data.data());
      }
      break;

    default:
      break;
  }
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
    makeit::Instance instance = stdout;
    return instance.init(argc, argv);
  }catch (const me::exception &e)
  {
    printf("catched me::exception: %s\n", e.get_message());
    return 1;
  }
}
