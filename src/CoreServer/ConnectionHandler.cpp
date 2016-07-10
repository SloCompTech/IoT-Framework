#include "ConnectionHandler.h"
ConnectionHandler::ConnectionHandler(TCPServerConnection pConnection)
{
  this->connection = pConnection;
  this->connection.setBlocking(false); /* So we can pass _receive() if nothing avaliable */
}
ConnectionHandler::~ConnectionHandler()
{
  this->connection.setBlocking(true);
}


bool ConnectionHandler::exec()
{

  string message = "";
  string tmp = "";

  if(this->connection._receive(message)!=0)/* If not disconnected */
  {
    if(message!="")
    {
      do
      {
        tmp = this->connection._receive();
        message+=tmp;
      }while(tmp!=""); /* If we get longer message than we can grab at one time */

      if(this->receiveCallback!=NULL)
        this->receiveCallback(this,message);


      message = "";
    }
    return true; /* Return true on success even if it is empty */
  }
  else
  {
    /*
      Error has happen
      usually client disconnected
    */
    if(this->disconnectCallback!=NULL)
      this->disconnectCallback(this);

    return false; /* Return false on error */
  }

}
bool ConnectionHandler::able()
{
  return this->connection.isValid();
}
void ConnectionHandler::close()
{
  this->connection._close();
}



TCPServerConnection ConnectionHandler::getConnection()
{
  return this->connection;
}

void ConnectionHandler::setConnection(TCPServerConnection pConnection)
{
  this->connection = pConnection;
}
void ConnectionHandler::setReceiveCallback(function<void(ConnectionHandler*,string)> pFunction)
{
  this->receiveCallback = pFunction;
}
void ConnectionHandler::setDisconnectCallback(function<void(ConnectionHandler*)> pFunction)
{
  this->disconnectCallback = pFunction;
}
