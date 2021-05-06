#ifndef MAKEIT_HPP
  #define MAKEIT_HPP

#include "Config.hpp"
#include "Logger.hpp"
#include "lexer/Lexer.hpp"
#include "parser/Parser.hpp"
#include "basic/Project.hpp"

namespace makeit {

  class Instance {

  protected:

    me::allocator alloc;

    Config config;
    Logger logger;

    Context context;
    Lexer lexer;
    Parser parser;

    ProjectVar project_var;
    TextVar* file_variable;
    TextVar* directory_variable;
    TextVar* main_target_variable;
    ArrayVar* targets_variable;

    TextVar* gmake_path_variable;
    TextVar* ycm_path_variable;

  public:

    Instance(FILE* log);

    int parse_args(int argc, char** argv);
    int init(int argc, char** argv);
    int init_variables();
    int init_functions();

    int print_usage() const;
    int print_version() const;

    int read_source(const me::string_view &path);

    int generate_target(TargetType target) const;

    int read_file(const me::string_view &path, size_t len, char* data) const;
    int write_file(const me::string_view &path, size_t len, char* data) const;

  };

}

#endif
