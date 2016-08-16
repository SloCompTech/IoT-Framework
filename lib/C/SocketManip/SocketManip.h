#ifndef LIB_SOCKETMANIP
#define LIB_SOCKETMANIP

#include <fcntl.h>

namespace SocketManip
{
  extern bool SetSocketBlockingEnabled(int fd, bool blocking);
}

#endif
