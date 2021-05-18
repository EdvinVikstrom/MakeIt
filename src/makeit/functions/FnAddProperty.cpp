#include "makeit/functions/FnAddProperty.hpp"
#include "makeit/basic/Project.hpp"

/* ------------------- */
/* class AddCFlagsFunc */
/* ------------------- */
makeit::AddCFlagsFunc::AddCFlagsFunc()
  : Function("add_cflags")
{
  static const me::vector<FuncArgument> variant1 = {
    {"flags", Variable::ARRAY}
  };
  static const me::vector<FuncArgument> variant2 = {
    {"lang", Variable::STRING},
    {"flags", Variable::ARRAY}
  };
  static const me::vector<FuncArgument> variant3 = {
    {"langs", Variable::ARRAY},
    {"flags", Variable::ARRAY}
  };

  variants.push_back(FuncVariant(1, variant1));
  variants.push_back(FuncVariant(2, variant2));
  variants.push_back(FuncVariant(3, variant3));
}

int makeit::AddCFlagsFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  /* Function variant 1 */
  if (variant.index == 1)
  {
    const ArrayVar::Value &flag_array = reinterpret_cast<ArrayVar*>(args.at(0))->value;
    for (const Variable* var : flag_array)
    {
      project.build_config.builder.compile_config.for_each(LANGUAGE_ALL, [var](CompileConfig &config, Language unused)
	  {config.options.push_back(reinterpret_cast<const StringVar*>(var)->value);});
    }

  /* Function variant 2 */
  }else if (variant.index == 2)
  {
    const Language lang = language_from_string(reinterpret_cast<StringVar*>(args.at(0))->value);
    const ArrayVar::Value &flag_array = reinterpret_cast<ArrayVar*>(args.at(1))->value;
    for (const Variable* var : flag_array)
    {
      project.build_config.builder.compile_config.for_each(lang, [var](CompileConfig &config, Language unused)
	  {config.options.push_back(reinterpret_cast<const StringVar*>(var)->value);});
    }
  /* Function variant 3 */
  }else if (variant.index == 3)
  {
    int langs = 0;
    const ArrayVar::Value &lang_array = reinterpret_cast<ArrayVar*>(args.at(0))->value;
    for (const Variable* var : lang_array)
    {
      langs |= language_from_string(reinterpret_cast<const StringVar*>(var)->value);
    }

    const ArrayVar::Value &flag_array = reinterpret_cast<ArrayVar*>(args.at(1))->value;
    for (const Variable* var : flag_array)
    {
      project.build_config.builder.compile_config.for_each(langs, [var](CompileConfig &config, Language unused)
	  {config.options.push_back(reinterpret_cast<const StringVar*>(var)->value);});
    }
  }
  return 0;
}
/* class end AddCFlagsFunc */


/* ------------------- */
/* class AddLFlagsFunc */
/* ------------------- */
makeit::AddLFlagsFunc::AddLFlagsFunc()
  : Function("add_lflags")
{
  static const me::vector<FuncArgument> variant1 = {
    {"flags", Variable::ARRAY}
  };

  variants.push_back(FuncVariant(1, variant1));
}

int makeit::AddLFlagsFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  const ArrayVar::Value &flag_array = reinterpret_cast<ArrayVar*>(args.at(0))->value;
  for (const Variable* var : flag_array)
  {
    project.build_config.builder.link_config.options.push_back(reinterpret_cast<const StringVar*>(var)->value);
  }
  return 0;
}
/* class end AddLFlagsFunc */


/* ------------------ */
/* class AddFlagsFunc */
/* ------------------ */
makeit::AddFlagsFunc::AddFlagsFunc()
  : Function("add_flags")
{
  static const me::vector<FuncArgument> variant1 = {
    {"flags", Variable::ARRAY}
  };

  variants.push_back(FuncVariant(1, variant1));
}

int makeit::AddFlagsFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  const ArrayVar::Value &flag_array = reinterpret_cast<ArrayVar*>(args.at(0))->value;
  for (const Variable* var : flag_array)
  {
    project.build_config.options.push_back(reinterpret_cast<const StringVar*>(var)->value);
  }
  return 0;
}
/* class end AddFlagsFunc */


/* -------------------- */
/* class AddIncludeFunc */
/* -------------------- */
makeit::AddIncludeFunc::AddIncludeFunc()
  : Function("add_include")
{
  static const me::vector<FuncArgument> variant1 = {
    {"paths", Variable::ARRAY}
  };
  static const me::vector<FuncArgument> variant2 = {
    {"lang", Variable::STRING},
    {"paths", Variable::ARRAY}
  };
  static const me::vector<FuncArgument> variant3 = {
    {"langs", Variable::ARRAY},
    {"paths", Variable::ARRAY}
  };

  variants.push_back(FuncVariant(1, variant1));
  variants.push_back(FuncVariant(2, variant2));
  variants.push_back(FuncVariant(3, variant3));
}

int makeit::AddIncludeFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  /* Function variant 1 */
  if (variant.index == 1)
  {
    const ArrayVar::Value &path_array = reinterpret_cast<ArrayVar*>(args.at(0))->value;
    for (const Variable* var : path_array)
    {
      project.build_config.builder.compile_config.for_each(LANGUAGE_ALL, [var](CompileConfig &config, Language unused)
	  {config.includes.emplace_back(reinterpret_cast<const StringVar*>(var)->value);});
    }

  /* Function variant 2 */
  }else if (variant.index == 2)
  {
    const Language lang = language_from_string(reinterpret_cast<StringVar*>(args.at(0))->value);
    const ArrayVar::Value &path_array = reinterpret_cast<ArrayVar*>(args.at(1))->value;
    for (const Variable* var : path_array)
    {
      project.build_config.builder.compile_config.for_each(lang, [var](CompileConfig &config, Language unused)
	  {config.includes.emplace_back(reinterpret_cast<const StringVar*>(var)->value);});
    }
  /* Function variant 3 */
  }else if (variant.index == 3)
  {
    int langs = 0;
    const ArrayVar::Value &lang_array = reinterpret_cast<ArrayVar*>(args.at(0))->value;
    for (const Variable* var : lang_array)
    {
      langs |= language_from_string(reinterpret_cast<const StringVar*>(var)->value);
    }

    const ArrayVar::Value &path_array = reinterpret_cast<ArrayVar*>(args.at(1))->value;
    for (const Variable* var : path_array)
    {
      project.build_config.builder.compile_config.for_each(langs, [var](CompileConfig &config, Language unused)
	  {config.includes.emplace_back(reinterpret_cast<const StringVar*>(var)->value);});
    }
  }
  return 0;
}
/* class end AddIncludeFunc */


/* ------------------------ */
/* class AddIncludePathFunc */
/* ------------------------ */
makeit::AddIncludePathFunc::AddIncludePathFunc()
  : Function("add_include_path")
{
  static const me::vector<FuncArgument> variant1 = {
    {"paths", Variable::ARRAY}
  };
  static const me::vector<FuncArgument> variant2 = {
    {"lang", Variable::STRING},
    {"paths", Variable::ARRAY}
  };
  static const me::vector<FuncArgument> variant3 = {
    {"langs", Variable::ARRAY},
    {"paths", Variable::ARRAY}
  };

  variants.push_back(FuncVariant(1, variant1));
  variants.push_back(FuncVariant(2, variant2));
  variants.push_back(FuncVariant(3, variant3));
}

int makeit::AddIncludePathFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  /* Function variant 1 */
  if (variant.index == 1)
  {
    const ArrayVar::Value &path_array = reinterpret_cast<ArrayVar*>(args.at(0))->value;
    for (const Variable* var : path_array)
    {
      project.build_config.builder.compile_config.for_each(LANGUAGE_ALL, [var](CompileConfig &config, Language unused)
	  {config.include_paths.emplace_back(reinterpret_cast<const StringVar*>(var)->value);});
    }

  /* Function variant 2 */
  }else if (variant.index == 2)
  {
    const Language lang = language_from_string(reinterpret_cast<StringVar*>(args.at(0))->value);
    const ArrayVar::Value &path_array = reinterpret_cast<ArrayVar*>(args.at(1))->value;
    for (const Variable* var : path_array)
    {
      project.build_config.builder.compile_config.for_each(lang, [var](CompileConfig &config, Language unused)
	  {config.include_paths.emplace_back(reinterpret_cast<const StringVar*>(var)->value);});
    }
  /* Function variant 3 */
  }else if (variant.index == 3)
  {
    int langs = 0;
    const ArrayVar::Value &lang_array = reinterpret_cast<ArrayVar*>(args.at(0))->value;
    for (const Variable* var : lang_array)
    {
      langs |= language_from_string(reinterpret_cast<const StringVar*>(var)->value);
    }

    const ArrayVar::Value &path_array = reinterpret_cast<ArrayVar*>(args.at(1))->value;
    for (const Variable* var : path_array)
    {
      project.build_config.builder.compile_config.for_each(langs, [var](CompileConfig &config, Language unused)
	  {config.include_paths.emplace_back(reinterpret_cast<const StringVar*>(var)->value);});
    }
  }
  return 0;
}
/* class end AddIncludePathFunc */


/* -------------------- */
/* class AddLibraryFunc */
/* -------------------- */
makeit::AddLibraryFunc::AddLibraryFunc()
  : Function("add_library")
{
  /* TODO: library type */
  static const me::vector<FuncArgument> variant1 = {
    {"library", Variable::ARRAY}
  };

  variants.push_back(FuncVariant(1, variant1));
}

int makeit::AddLibraryFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  const ArrayVar::Value &library_array = reinterpret_cast<ArrayVar*>(args.at(0))->value;
  for (const Variable* var : library_array)
  {
    project.build_config.builder.link_config.libraries.emplace_back(Library::STATIC, reinterpret_cast<const StringVar*>(var)->value);
  }
  return 0;
}
/* class end AddLibraryFunc */


/* ------------------------ */
/* class AddLibraryPathFunc */
/* ------------------------ */
makeit::AddLibraryPathFunc::AddLibraryPathFunc()
  : Function("add_library_path")
{
  static const me::vector<FuncArgument> variant1 = {
    {"path", Variable::ARRAY}
  };

  variants.push_back(FuncVariant(1, variant1));
}

int makeit::AddLibraryPathFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  const ArrayVar::Value &path_array = reinterpret_cast<ArrayVar*>(args.at(0))->value;
  for (const Variable* var : path_array)
  {
    project.build_config.builder.link_config.library_paths.emplace_back(reinterpret_cast<const StringVar*>(var)->value);
  }
  return 0;
}
/* class end AddLibraryPathFunc */


/* -------------------- */
/* class AddPackageFunc */
/* -------------------- */
makeit::AddPackageFunc::AddPackageFunc()
  : Function("add_package")
{
  static const me::vector<FuncArgument> variant1 = {
  };

  variants.push_back(FuncVariant(1, variant1));
}

int makeit::AddPackageFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  return 0;
}
/* class end AddPackageFunc */
