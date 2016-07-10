#include "TCPClient.h"
TCPClient::TCPClient()
{
  this->obj_socket = -1; /* NULL Socket */
  this->Address = ""; /* No IP address */
  this->Port = 0; /* NULL Port */
}

TCPClient::~TCPClient()
{
  /*if(this->isValid())
    this->_close();*/
}

bool TCPClient::setBlocking(bool pBlocking)
{
  this->blocking = pBlocking;
  return SocketManip::SetSocketBlockingEnabled(this->obj_socket,pBlocking);
}

string TCPClient::getAddress()
{
  return this->Address;
}

int TCPClient::getPort()
{
  return this->Port;
}

bool TCPClient::isOpened()
{
  return this->isValid();
}

bool TCPClient::isValid()
{
  return ((this->obj_socket) > -1);
}

bool TCPClient::_connect(string pAddress,int pPort)
{
  struct addrinfo hints, *servinfo, *p;
  char port[4];

  Convert::itocs(pPort,port);

  int rv,yes=1;

  //Set properties of socket
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC; //Use IPv4 and IPv6
  hints.ai_socktype = SOCK_STREAM;


  bool done = false;
  switch(true)
  {
    case true:
      if ((rv = getaddrinfo(pAddress.c_str(), port, &hints, &servinfo)) != 0) {
         fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
         break;
      }
      // loop through all the results and bind to the first we can
      for(p = servinfo; p != NULL; p = p->ai_next) {
          if (((this->obj_socket) = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) {
              perror("server: socket");
              continue;
          }

          if (connect(this->obj_socket, p->ai_addr, p->ai_addrlen) == -1) {
              close(this->obj_socket);
              perror("client: connect");
              continue;
          }
          done = true;
          break;
      }

  }


  freeaddrinfo(servinfo); // all done with this structure

  if(p==NULL||!done)
    return false;


  /* Add info to porperties of client */
  this->Address = pAddress;
  this->Port = pPort;

  return true;
}


bool TCPClient::_send(string message)
{
  if(send(this->obj_socket,message.c_str(),message.size(),0)>-1)
    return true;
  else
    return false;
}
bool TCPClient::_send(const char message[])
{
  if(send(this->obj_socket,message,strlen(message),0)>-1)
    return true;
  else
    return false;
}
string TCPClient::_receive()
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
string TCPClient::_receive(int pSize)
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

int TCPClient::_receive(string &pString)
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
int TCPClient::_receive(int pSize,string &pString)
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


void TCPClient::clearBuffer()
{
  bool realBlocking = this->blocking;
  if(realBlocking)
    this->setBlocking(false);

  while(this->_receive()!="")
    ;

  if(realBlocking)
    this->setBlocking(true);
}

void TCPClient::_close()
{
  close(this->obj_socket);
  this->Address = "";
  this->Port = 0;

}

void TCPClient::setBufferSize(int size)
{
  if(size>=1)
    this->bufferSize = size;
}

int TCPClient::getBufferSize()
{
  return this->bufferSize;
}

void TCPClient::setSafeMode(bool pMode)
{
  this->safeMode = pMode;
}
bool TCPClient::getSafeMode()
{
  return this->safeMode;
}
