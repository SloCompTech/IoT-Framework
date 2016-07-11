#ifndef LIB_NET
#define LIB_NET

#include <string>

namespace Net
{
  namespace Socket
  {
    struct SocketInfo
    {
      std::string address;
      int port;

      SocketInfo()
      {
        this->address = "";
        this->port = 0;
      }
    };
  }
}

#endif
