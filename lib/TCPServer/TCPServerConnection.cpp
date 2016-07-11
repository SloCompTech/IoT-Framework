#include "TCPServerConnection.h"

TCPServerConnection::TCPServerConnection()
{

}

TCPServerConnection::TCPServerConnection(int pSocket)
{
    this->obj_socket = pSocket;
}
TCPServerConnection::~TCPServerConnection()
{
  if(this->safeMode&&this->isValid())
    this->_close();
}

bool TCPServerConnection::setBlocking(bool pBlocking)
{
  this->blocking = pBlocking;
  return SocketManip::SetSocketBlockingEnabled(this->obj_socket,pBlocking);
}



struct Net::Socket::SocketInfo TCPServerConnection::getInfo()
{
  struct Net::Socket::SocketInfo sinfo;
  if(!this->isValid())
    return sinfo;

  socklen_t len;
  struct sockaddr_storage addr;
  char ipstr[INET6_ADDRSTRLEN];
  int port;
  len = sizeof(addr);
  getpeername(this->obj_socket, (struct sockaddr*)&addr, &len);

  // deal with both IPv4 and IPv6:
  if (addr.ss_family == AF_INET) {
      struct sockaddr_in *s = (struct sockaddr_in *)&addr;
      port = ntohs(s->sin_port);
      inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
  } else { // AF_INET6
      struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
      port = ntohs(s->sin6_port);
      inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
  }

  sinfo.address = (string)ipstr;
  sinfo.port = port;

  return sinfo;
}

string TCPServerConnection::getAddress()
{
  return this->getInfo().address;
}
int TCPServerConnection::getPort()
{
  return this->getInfo().port;
}

bool TCPServerConnection::isOpened()
{
  return this->isValid();
}

bool TCPServerConnection::isValid()
{
  return ((this->obj_socket) > -1);
}

bool TCPServerConnection::_send(string message)
{
  if(!this->isValid())
    return false;

  if(send(this->obj_socket,message.c_str(),message.size(),0)>-1)
    return true;
  else
    return false;
}
bool TCPServerConnection::_send(const char message[])
{
  if(!this->isValid())
    return false;

  if(send(this->obj_socket,message,strlen(message),0)>-1)
    return true;
  else
    return false;
}
string TCPServerConnection::_receive()
{
  if(!this->isValid())
    return "";

  char buffer[this->bufferSize+1];
  int len = recv(this->obj_socket, buffer, this->bufferSize, 0);
  if(len>-1)
  {
    buffer[len]='\0';
    return (string)buffer;
  }
  else
    return "";
}
string TCPServerConnection::_receive(int pSize)
{
  char buffer[pSize+1];
  int len = recv(this->obj_socket, buffer, pSize, 0);
  if(len>-1)
  {
    buffer[len]='\0';
    return (string)buffer;
  }
  else
    return "";
}
int TCPServerConnection::_receive(string &pString)
{
  if(!this->isValid())
    return -1;

  char buffer[this->bufferSize+1];
  int len = recv(this->obj_socket, buffer, this->bufferSize, 0);
  if(len>-1)
  {
    buffer[len]='\0';
    pString = (string)buffer;
    return len;
  }
  else
    return -1;
}
int TCPServerConnection::_receive(int pSize,string &pString)
{
  if(!this->isValid())
    return -1;

  char buffer[pSize+1];
  int len = recv(this->obj_socket, buffer, pSize, 0);
  if(len>-1)
  {
    buffer[len]='\0';
    pString = (string)buffer;
    return len;
  }
  else
    return -1;
}

void TCPServerConnection::clearBuffer()
{
  bool realBlocking = this->blocking;
  if(realBlocking)
    this->setBlocking(false);

  while(this->_receive()!="")
    ;

  if(realBlocking)
    this->setBlocking(true);

}

void TCPServerConnection::_close()
{
  close(this->obj_socket);
}

void TCPServerConnection::setBufferSize(int size)
{
  if(size>=1)
    this->bufferSize = size;
}

int TCPServerConnection::getBufferSize()
{
  return this->bufferSize;
}
void TCPServerConnection::setSafeMode(bool pMode)
{
  this->safeMode = pMode;
}
bool TCPServerConnection::getSafeMode()
{
  return this->safeMode;
}
