#ifndef LIB_TCPCLIENT
#define LIB_TCPCLIENT

#ifndef OS_LINUX
  #define OS_LINUX
#endif

#include <string>
#include <cstring>

#include <unistd.h>

#include <SocketManip/SocketManip.h>

#ifdef OS_LINUX
  #include <netinet/in.h>
  #include <netdb.h>
  #include <sys/socket.h>
  #include <sys/types.h>
  #include <arpa/inet.h>
#endif

using namespace std;

class TCPClient
{
  public:

    ~TCPClient();

    bool setBlocking(bool pBlocking);
    string getAddress();

    bool isValid();
    bool isOpened();

    bool _connect(string pAddress,int pPort);

    bool _send(string message);
    bool _send(const char message[]);

    string _receive();
    string _receive(int pSize);

    void _close();

    void setBufferSize(int size);
    int getBufferSize();

  private:
    int obj_socket;
    int bufferSize = 1024; /*Number of bytes we receive at same time */

    struct sockaddr_storage obj_addr;
    void *get_in_addr(struct sockaddr *sa);

};

#endif
