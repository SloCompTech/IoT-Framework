#include "Log.h"

namespace Log
{
  void logInfo(string message)
  {
    cout << "[Info] "<< message << endl;
  }
  void logWarning(string message)
  {
    cout << "[Warn] "<< message << endl;
  }
  void logError(string message)
  {
    cout << "[Error] "<< message << endl;
  }
  void logDebug(string message)
  {
    cout << "[Debug] " << message << endl; 
  }
}
