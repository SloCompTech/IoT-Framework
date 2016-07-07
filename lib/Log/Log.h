#ifndef LIB_LOG
#define LIB_LOG

#include <iostream>
#include <string>

using namespace std;

namespace Log
{
  extern void logInfo(string message);
  extern void logWarning(string message);
  extern void logError(string message);
  extern void logDebug(string message);
}
#endif
