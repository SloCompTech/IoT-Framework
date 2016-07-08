#include "TCPServerConnection.h"

TCPServerConnection::TCPServerConnection(int pSocket,struct sockaddr_storage pSa)
{
    this->obj_socket = pSocket;
    this->obj_addr = pSa;
}
TCPServerConnection::~TCPServerConnection()
{
  if(this->isValid())
    this->_close();
}

bool TCPServerConnection::setBlocking(bool pBlocking)
{
  this->blocking = pBlocking;
  return SocketManip::SetSocketBlockingEnabled(this->obj_socket,pBlocking);
}

void *TCPServerConnection::get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

string TCPServerConnection::getAddress()
{
  char s[INET6_ADDRSTRLEN];
  inet_ntop((this->obj_addr).ss_family,get_in_addr((struct sockaddr *)&(this->obj_addr)),s, sizeof s);
  return (string)s;
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
  if(send(this->obj_socket,message.c_str(),message.size(),0)>-1)
    return true;
  else
    return false;
}
bool TCPServerConnection::_send(const char message[])
{
  if(send(this->obj_socket,message,strlen(message),0)>-1)
    return true;
  else
    return false;
}
string TCPServerConnection::_receive()
{
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
