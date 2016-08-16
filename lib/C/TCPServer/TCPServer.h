#ifndef LIB_TCPSERVER
#define LIB_TCPSERVER

#ifndef OS_LINUX
  #define OS_LINUX
#endif

#include <string>
#include <unistd.h>

#include <SocketManip/SocketManip.h>
#include "TCPServerConnection.h"
#include <Convert/Convert.h>

#ifdef OS_LINUX
  #include <netinet/in.h>
  #include <netdb.h>
  #include <sys/socket.h>
  #include <sys/types.h>
  #include <arpa/inet.h>
#endif

using namespace std;

class TCPServer
{
  public:
    ~TCPServer();
    bool isOpened();
    bool isValid();

    void setMaxPendingConnections(int pNumber);
    int getMaxPendingConnections();
    bool setBlocking(bool pBlocking);

    bool _bind(int pPort);
    bool _listen();

    TCPServerConnection _accept();

    void _close();

    void setSafeMode(bool pMode);
    bool getSafeMode();

    string getHostname();
  private:
    int obj_socket;
    int pendingConnections = 10; //Number of pending connection to hold
    bool safeMode = true;
};


#endif
