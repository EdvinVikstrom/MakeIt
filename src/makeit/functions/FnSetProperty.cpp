#include "makeit/functions/FnSetProperty.hpp"
#include "makeit/basic/Project.hpp"

/* --------------------------- */
/* class SetBuildDirectoryFunc */
/* --------------------------- */
makeit::SetBuildDirectoryFunc::SetBuildDirectoryFunc()
  : Function("set_build_directory")
{
  static const me::vector<FuncArgument> variant1 = {
    {"directory", Variable::STRING}
  };

  variants.push_back(FuncVariant(1, variant1));
}

int makeit::SetBuildDirectoryFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  project.build_config.builder.directory = reinterpret_cast<StringVar*>(args.at(0))->value;
  return 0;
}
/* class end SetBuildDirectoryFunc */


/* ---------------------------- */
/* class SetBinaryDirectoryFunc */
/* ---------------------------- */
makeit::SetBinaryDirectoryFunc::SetBinaryDirectoryFunc()
  : Function("set_binary_directory")
{
  static const me::vector<FuncArgument> variant1 = {
    {"directory", Variable::STRING}
  };

  variants.push_back(FuncVariant(1, variant1));
}

int makeit::SetBinaryDirectoryFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  project.build_config.builder.compile_config.for_each(LANGUAGE_ALL, [args](CompileConfig &config, Language unused)
      {config.compiler.directory = reinterpret_cast<StringVar*>(args.at(0))->value;});
  project.build_config.builder.link_config.linker.directory = reinterpret_cast<StringVar*>(args.at(0))->value;
  return 0;
}
/* class end SetBinaryDirectoryFunc */


/* ------------------- */
/* class SetOutputFunc */
/* ------------------- */
makeit::SetOutputFunc::SetOutputFunc()
  : Function("set_output")
{
  static const me::vector<FuncArgument> variant1 = {
    {"output", Variable::STRING}
  };

  variants.push_back(FuncVariant(1, variant1));
}

int makeit::SetOutputFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  project.build_config.builder.output = reinterpret_cast<StringVar*>(args.at(0))->value;
  return 0;
}
/* class end SetOutputFunc */


/* --------------------- */
/* class SetLanguageFunc */
/* --------------------- */
makeit::SetLanguageFunc::SetLanguageFunc()
  : Function("set_language")
{
  static const me::vector<FuncArgument> variant1 = {
    {"lang", Variable::STRING}
  };

  variants.push_back(FuncVariant(1, variant1));
}

int makeit::SetLanguageFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  project.build_config.builder.lang = language_from_string(reinterpret_cast<StringVar*>(args.at(0))->value);
  return 0;
}
/* class end SetLanguageFunc */


/* ----------------- */
/* class SetKindFunc */
/* ----------------- */
makeit::SetKindFunc::SetKindFunc()
  : Function("set_kind")
{
  static const me::vector<FuncArgument> variant1 = {
    {"kind", Variable::STRING}
  };

  variants.push_back(FuncVariant(1, variant1));
}

int makeit::SetKindFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  project.build_config.builder.kind = kind_from_string(reinterpret_cast<StringVar*>(args.at(0))->value);
  return 0;
}
/* class end SetKindFunc */


/* --------------------- */
/* class SetCompilerFunc */
/* --------------------- */
makeit::SetCompilerFunc::SetCompilerFunc()
  : Function("set_compiler")
{
  static const me::vector<FuncArgument> variant1 = {
    {"compiler", Variable::STRING}
  };
  static const me::vector<FuncArgument> variant2 = {
    {"lang", Variable::STRING},
    {"compiler", Variable::STRING}
  };
  static const me::vector<FuncArgument> variant3 = {
    {"langs", Variable::ARRAY},
    {"compiler", Variable::STRING}
  };

  variants.push_back(FuncVariant(1, variant1));
  variants.push_back(FuncVariant(2, variant2));
  variants.push_back(FuncVariant(3, variant3));
}

int makeit::SetCompilerFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  /* Function variant 1 */
  if (variant.index == 1)
  {
    project.build_config.builder.compile_config.for_each(LANGUAGE_ALL, [args](CompileConfig &config, Language lang)
	{config.compiler.name = identify_compiler_name(reinterpret_cast<const StringVar*>(args.at(0))->value, lang);});

  /* Function variant 2 */
  }else if (variant.index == 2)
  {
    project.build_config.builder.compile_config.for_each(language_from_string(reinterpret_cast<StringVar*>(args.at(0))->value),
	[args](CompileConfig &config, Language lang) {config.compiler.name = identify_compiler_name(
	  reinterpret_cast<const StringVar*>(args.at(1))->value, lang);});

  /* Function variant 3 */
  }else if (variant.index == 3)
  {
    int langs = 0;
    const ArrayVar::Value &lang_array = reinterpret_cast<ArrayVar*>(args.at(0))->value;
    for (me::size_t i = 0; i != lang_array.size(); i++)
    {
      const Variable* var = lang_array.at(i);
      langs |= language_from_string(reinterpret_cast<const StringVar*>(var)->value);
    }
    project.build_config.builder.compile_config.for_each(langs, [args](CompileConfig &config, Language lang)
	{config.compiler.name = identify_compiler_name(reinterpret_cast<const StringVar*>(args.at(1))->value, lang);});
  }
  return 0;
}
/* class end SetCompilerFunc */


/* ------------------- */
/* class SetLinkerFunc */
/* ------------------- */
makeit::SetLinkerFunc::SetLinkerFunc()
  : Function("set_linker")
{
  static const me::vector<FuncArgument> variant1 = {
    {"linker", Variable::STRING}
  };
  static const me::vector<FuncArgument> variant2 = {
    {"linker", Variable::STRING},
    {"lang", Variable::STRING}
  };

  variants.push_back(FuncVariant(1, variant1));
}

int makeit::SetLinkerFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  /* Function variant 1 */
  if (variant.index == 1)
  {
    project.build_config.builder.link_config.linker.name = identify_linker_name(
	reinterpret_cast<StringVar*>(args.at(0))->value, project.build_config.builder.lang);

  /* Function variant 2 */
  }else if (variant.index == 2)
  {
    /* TODO: what if lang is 'ALL'? */
    project.build_config.builder.link_config.linker.name = identify_linker_name(
	reinterpret_cast<StringVar*>(args.at(1))->value,
	language_from_string(reinterpret_cast<StringVar*>(args.at(0))->value));
  }
  return 0;
}
/* class end SetLinkerFunc */


/* ----------------------- */
/* class SetSystemRootFunc */
/* ----------------------- */
makeit::SetSystemRootFunc::SetSystemRootFunc()
  : Function("set_system_root")
{
  static const me::vector<FuncArgument> variant1 = {
    {"directory", Variable::STRING}
  };

  variants.push_back(FuncVariant(1, variant1));
}

int makeit::SetSystemRootFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  project.build_config.system_root.path = reinterpret_cast<StringVar*>(args.at(0))->value;
  return 0;
}
/* class end SetSystemRootFunc */


/* ----------------------- */
/* class SetTargetArchFunc */
/* ----------------------- */
makeit::SetTargetArchFunc::SetTargetArchFunc()
  : Function("set_target_arch")
{
  static const me::vector<FuncArgument> variant1 = {
    {"arch", Variable::STRING}
  };

  variants.push_back(FuncVariant(1, variant1));
}

int makeit::SetTargetArchFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  project.build_config.target_arch.arch = reinterpret_cast<StringVar*>(args.at(0))->value;
  return 0;
}
/* class end SetTargetArchFunc */
