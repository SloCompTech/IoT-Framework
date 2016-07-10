#ifndef EXT_CONNECTIONHANDLER
#define EXT_CONNECTIONHANDLER

#include <TCPServer/TCPServerConnection.h>
#include <string>
#include <iostream>
#include <functional>

using namespace std;

class ConnectionHandler
{
  public:
      ConnectionHandler(TCPServerConnection pConnection);
      ~ConnectionHandler();

      bool exec();
      void close();
      bool able();

      void setConnection(TCPServerConnection pConnection);
      TCPServerConnection getConnection();

      void setReceiveCallback(function<void(ConnectionHandler*,string)> pFunction);
      void setDisconnectCallback(function<void(ConnectionHandler*)> pFunction);
  private:
      TCPServerConnection connection;
      function<void(ConnectionHandler*,string)> receiveCallback = NULL;
      function<void(ConnectionHandler*)> disconnectCallback = NULL;

};



#endif
