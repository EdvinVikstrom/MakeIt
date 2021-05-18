#ifndef MAKEIT_HPP
  #define MAKEIT_HPP

#include "Logger.hpp"
#include "lexer/Lexer.hpp"
#include "parser/Parser.hpp"
#include "basic/Project.hpp"

namespace makeit {

  class Instance {

  protected:

    me::allocator alloc;

    Logger logger;

    Context context;
    Lexer lexer;
    Parser parser;

    StringVar* file_variable;
    StringVar* directory_variable;
    StringVar* main_target_variable;
    ArrayVar* targets_variable;
    StringVar* gmake_path_variable;
    StringVar* ycm_path_variable;

  public:

    Instance(FILE* log);

    int parse_args(int argc, char** argv);
    int init(int argc, char** argv);
    int init_variables();
    int init_functions();

    int print_usage() const;
    int print_version() const;

    int read_source(const me::string_view &path);

    int generate_targets() const;
    int generate_target(const me::string_view &target) const;

    int read_file(const me::string_view &path, size_t len, char* data) const;
    int write_file(const me::string_view &path, size_t len, char* data) const;

  };

  extern Instance instance;

}

#endif
