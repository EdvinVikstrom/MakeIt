#include "makeit/basic/Project.hpp"
#include "makeit/Common.hpp"
#include "makeit/Config.hpp"

/* ------------- */
/* struct Source */
/* ------------- */
makeit::Source::Source(const me::string_view &source)
  : source(source), language(identify_file(source))
{
}

makeit::Source::Source(const me::string_view &source, Language language)
  : source(source), language(language)
{
}

char* makeit::Source::string_write(char* buffer) const
{
  const char* iter = source.begin();
  while (iter != source.end())
    *buffer++ = *iter++;
  return buffer;
}

me::string& makeit::Source::string_write(me::string &buffer) const
{
  buffer.append(source);
  return buffer;
}

char* makeit::Source::string_write(const me::string_view &build_directory, char* buffer) const
{
  const char* iter1 = build_directory.begin();
  while (iter1 != build_directory.end())
    *buffer++ = *iter1++;

  if (!build_directory.ends_with("/"))
    *buffer++ = '/';

  const char* iter2 = source.begin();
  while (iter2 != source.end())
    *buffer++ = *iter2++;

  *buffer++ = '.';

  const char* iter3 = OBJECT_SUFFIX.begin();
  while (iter3 != OBJECT_SUFFIX.end())
    *buffer++ = *iter3++;
  return buffer;
}

me::string& makeit::Source::string_write(const me::string_view &build_directory, me::string &buffer) const
{
  buffer.append(build_directory);

  if (!build_directory.ends_with("/"))
    buffer += '/';

  buffer.append(source).append('.').append(OBJECT_SUFFIX);
  return buffer;
}
/* struct end Source */


/* --------------- */
/* struct External */
/* --------------- */
makeit::External::External(const me::string_view &command, const me::string_view &output)
  : command(command), output(output)
{
}
/* struct end External */


/* ------------------- */
/* struct Installation */
/* ------------------- */
makeit::Installation::Installation(const me::string_view &source, const me::string_view &directory)
  : source(source), directory(directory)
{
}
/* struct end Installation */


makeit::Language makeit::identify_file(const me::string_view &file)
{
  static const me::vector<me::string_view> suffix_c = {
    ".C", ".H"
  };
  static const me::vector<me::string_view> suffix_cxx = {
    ".CPP", ".CXX", ".CC", ".C++", ".HPP", ".HXX", ".HH", ".H++"
  };
  static const me::vector<me::string_view> suffix_objc = {
    ".IDK"
  };

  for (const me::string_view &suffix : suffix_c)
  {
    if (file.ends_with_ignore_case(suffix))
      return LANGUAGE_C;
  }

  for (const me::string_view &suffix : suffix_cxx)
  {
    if (file.ends_with_ignore_case(suffix))
      return LANGUAGE_CXX;
  }

  for (const me::string_view &suffix : suffix_objc)
  {
    if (file.ends_with_ignore_case(suffix))
      return LANGUAGE_OBJECTIVE_C;
  }

  return LANGUAGE_INVALID;
}
