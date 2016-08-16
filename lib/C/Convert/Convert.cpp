#include "Convert.h"

namespace Convert
{
  void itocs(int pInt,char cstr[])
  {
    std::ostringstream ostr;
    ostr<<pInt;
    strcpy(cstr,ostr.str().c_str());
  }
}
