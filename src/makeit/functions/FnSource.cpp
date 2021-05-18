#include "makeit/functions/FnSource.hpp"
#include "makeit/MakeIt.hpp"
#include "makeit/Text.hpp"

namespace makeit {

  static const me::vector<FuncArgument> variant1 = {
    {"file", Variable::STRING},
  };

}

makeit::SourceFunc::SourceFunc()
  : Function("source")
{
  variants.push_back(FuncVariant(1, variant1));
}

int makeit::SourceFunc::execute(const FuncVariant &variant, const me::vector<Variable*> &args, Context &context)
{
  for (me::size_t i = 0; i < args.size(); i++)
  {
    Variable* var = args.at(i);
    instance.read_source(reinterpret_cast<StringVar*>(var)->value);
  }
  return 0;
}
