#include "TCPServer.h"

TCPServer::~TCPServer()
{
  if(this->isOpened())
    this->_close();
}

bool TCPServer::isValid()
{
  return (this->obj_socket) > -1;
}
bool TCPServer::isOpened()
{
  return this->isValid();
}

void TCPServer::setMaxPendingConnections(int number)
{

  if(number>SOMAXCONN)
    this->pendingConnections = SOMAXCONN; /*If we pass maximum */
  else if(number>0)
    this->pendingConnections = number;
}
int TCPServer::getMaxPendingConnections()
{
  return this->pendingConnections;
}


bool TCPServer::setBlocking(bool pBlocking)
{
  return SocketManip::SetSocketBlockingEnabled(this->obj_socket,pBlocking);
}



bool TCPServer::_bind(int pPort)
{
  struct addrinfo hints, *servinfo, *p;
  char port[4];

  Convert::itocs(pPort,port);

  int rv,yes=1;

  //Set properties of socket
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC; //Use IPv4 and IPv6
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; // Use my IP



  bool done = false;
  switch(true)
  {
    case true:
      if ((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
         fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
         break;
      }
      // loop through all the results and bind to the first we can
      for(p = servinfo; p != NULL; p = p->ai_next) {
          if (((this->obj_socket) = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) {
              perror("server: socket");
              continue;
          }

          if (setsockopt(this->obj_socket, SOL_SOCKET, SO_REUSEADDR, &yes,
                  sizeof(int)) == -1) {
              perror("setsockopt");
              break;
          }

          if (bind(this->obj_socket, p->ai_addr, p->ai_addrlen) == -1) {
              close(this->obj_socket);
              perror("server: bind");
              continue;
          }
          done = true;
          break;
      }

  }

  freeaddrinfo(servinfo); // all done with this structure

  if(p==NULL||!done)
    return false;


  freeaddrinfo(p);


  return true;
}

bool TCPServer::_listen()
{
  return listen(this->obj_socket,this->pendingConnections)==0;
}

TCPServerConnection TCPServer::_accept()
{
  socklen_t sin_size;
  struct sockaddr_storage their_addr;
  int socket = accept(this->obj_socket, (struct sockaddr *)&their_addr, &sin_size);
  TCPServerConnection servConn(socket,their_addr);
  return servConn;
}


void TCPServer::_close()
{
  close(this->obj_socket);
}
