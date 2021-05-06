#ifndef MAKEIT_TEXT_HPP
  #define MAKEIT_TEXT_HPP

namespace makeit {

  namespace Text {

    extern const char* Eunknown_language; /* "unknown language '%s'" */
    extern const char* Eunknown_kind; /* "unknown kind '%s'" */
    extern const char* Eunknown_compiler; /* "unknown compiler '%s'" */
    extern const char* Eunknown_library; /* "unknown library type '%s'" */
    extern const char* Eunknown_external; /* "unknown external '%s'" */
    extern const char* Eunknown_target; /* "unknown target '%s'" */

    extern const char* Ecannot_copy_type; /* "cannot copy with temporary variable" */
    extern const char* Ecannot_assign_type; /* "cannot assign with temporary variable" */
    extern const char* Ecannot_append_type; /* "cannot append with temporary variable" */
    extern const char* Ecannot_compare_type; /* "cannot compare with temporary variable" */

    extern const char* Ecannot_assign_types; /* "cannot assign variable with type '%s' with variable with another type '%s'" */
    extern const char* Ecannot_append_types; /* "cannot append variable with type '%s' with variable with another type '%s'" */
    extern const char* Ecannot_compare_types; /* "cannot compare variable with type '%s' with variable with another type '%s'" */

    extern const char* Scompile_source; /* "compiling source '%s'" */

  }

}

#endif
