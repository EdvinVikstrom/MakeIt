#include "makeit/Text.hpp"
#include "makeit/Common.hpp"

namespace makeit::Text {

  const char* Eunknown_language = _("unknown language '%s'");
  const char* Eunknown_kind = _("unknown kind '%s'");
  const char* Eunknown_compiler = _("unknown compiler '%s'");
  const char* Eunknown_library = _("unknown library type '%s'");
  const char* Eunknown_external = _("unknown external '%s'");
  const char* Eunknown_target = _("unknown target '%s'");

  const char* Ecannot_copy_type = _("cannot copy with variable type '%s'");
  const char* Ecannot_assign_type = _("cannot assign with variable type '%s'");
  const char* Ecannot_append_type = _("cannot append with variable type '%s'");
  const char* Ecannot_compare_type = _("cannot compare with variable type '%s'");

  const char* Ecannot_assign_types = _("cannot assign variable with type '%s' with variable with another type '%s'");
  const char* Ecannot_append_types = _("cannot append variable with type '%s' with variable with another type '%s'");
  const char* Ecannot_compare_types = _("cannot compare variable with type '%s' with variable with another type '%s'");
 
  const char* Scompile_source = _("compiling source '$<'");
}
