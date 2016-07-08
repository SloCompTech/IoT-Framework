#ifndef LIB_TCPSERVER_CONNECTION
#define LIB_TCPSERVER_CONNECTION

#ifndef OS_LINUX
  #define OS_LINUX
#endif

#include <string>
#include <cstring>

#include <SocketManip/SocketManip.h>
#include <unistd.h>

#ifdef OS_LINUX
  #include <netinet/in.h>
  #include <netdb.h>
  #include <sys/socket.h>
  #include <sys/types.h>
  #include <arpa/inet.h>
#endif

using namespace std;

class TCPServerConnection
{
  public:
    TCPServerConnection(int pSocket,struct sockaddr_storage pSa);
    ~TCPServerConnection();

    bool setBlocking(bool pBlocking);
    string getAddress();

    bool isValid();
    bool isOpened();

    bool _send(string message);
    bool _send(const char message[]);

    string _receive();
    string _receive(int pSize);

    void _close();

    void setBufferSize(int size);
    int getBufferSize();

    void clearBuffer();

  private:
    int obj_socket;
    int bufferSize=1024; /* Number of bytes we can receive at once */
    struct sockaddr_storage obj_addr;
    void *get_in_addr(struct sockaddr *sa);
    bool blocking = true;
};

#endif
