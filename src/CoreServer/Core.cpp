#define OS_LINUX

#include <iostream>
#include <vector>
#include <string>
#include <thread>

#include <csignal>
#include <cstdlib>
#include <cstdio>

#include <TCPServer/TCPServer.h>
#include <TCPServer/TCPServerConnection.h>
#include <ProcessManip/ProcessManip.h>
#include <Log/Log.h>

#include <jsonrpc/jsonrpc.h>
#include <jsoncpp/dist/json/json.h>
#include <jsoncpp/dist/json/json-forwards.h>

#include "ConnectionHandler.h"

//Global
bool TERMNINATE = false;//If true loops must end
const int PORT = 8822;
vector<ConnectionHandler> clients;

//Proto
void terminate(int sig);
void receive_message(ConnectionHandler *handler,string message);
void process_cmd(ConnectionHandler *handler,string message);
void tcp_worker();
void printstring(string text);

using namespace std;

int main(int argc,char *argv[])
{
  //Add Terminate handler
  signal(SIGINT,terminate);

  //Load configuration
  Log::logDebug("Starting ...");

  //Init
  thread t_tcpworker(tcp_worker);

  //Init modules

  //Main
  Log::logDebug("Running");
  TCPServer server;

  if(!server._bind(PORT))
    return 1;

  if(!server._listen())
    return 2;

  ProcessManip::cleanProcess(); /*  Clean dead processes */

  server.setBlocking(false);/* accept returns invalid socket if no connection */
  Log::logDebug("Listening ...");
  while(!TERMNINATE)
  {
    ConnectionHandler* ch = new ConnectionHandler(*(new TCPServerConnection(server._accept())));
    if(!ch->getConnection().isValid())
    {
      delete ch;
      continue;
    }
    Log::logDebug((string)"Got connection from: "+ch->getConnection().getAddress());/* Print IP address of client */


    ch->setReceiveCallback(receive_message);
    clients.push_back(*ch);

    Log::logDebug("Connection added to vector");
  }
  server.setBlocking(true);

  //Dispose
  Log::logDebug("Stopping ...");
  if(t_tcpworker.joinable())
    t_tcpworker.join(); //Wait worker to end
  Log::logDebug("Disconnecting ...");
  for(auto it = clients.begin();it!=clients.end();)
  {
      Log::logDebug((string)"Closed connection with: "+(*it).getConnection().getAddress());/* Print IP address of client */
      (*it).close(); /* Close connetion */
      it = clients.erase(it); /* Delete ConnectionHandler from vector */
  }

  server._close();

  Log::logDebug("Closed");
  return 0;
}

void terminate(int sig)
{
  //Change global value to true
  TERMNINATE = true;
}

void receive_message(ConnectionHandler *handler,string message)
{

  if(message!="\n"&&message!="\n\r"&&message!=""&&message!="\r\n")
  {
    Log::logDebug((string)"Message ("+handler->getConnection().getAddress()+") : "+message);
    process_cmd(handler,message);
  }
  else
  {
    Log::logDebug((string)"Message ("+handler->getConnection().getAddress()+") : <empty message>");
    printstring(message);
  }

}

void process_cmd(ConnectionHandler *handler,string message)
{
  JsonRPC json;
  JsonRPC response("2.0");

  try
  {
    if(json.parse(message))
    {
      int type = json.getType();
      if(type!=JsonRPC::Type::None)
      {
        string method = json.getMethod();
        Json::Value params = json.getParams();

        if(method == "auth")
        {
          // Authentication (key (on-boot) or token)

        }
        else if(method == "storeval")
        {
          // Store value in db

        }


        handler->getConnection()._send(message); /* Repeat message */
      }
      else
      {
        //Invalid RPC request
        response.setErrorCode(-32600);
        response.setErrorMessage("Invalid request");
        handler->getConnection()._send(response.str()+"\r\n");
      }
    }
    else
    {
        //Parse error
        response.setErrorCode(-32700);
        response.setErrorMessage("Parse error");
        handler->getConnection()._send(response.str()+"\r\n");
    }
  }catch (Json::LogicError e){
    cout << e.what() << endl;
    //Parse error
    try
    {
      response.setErrorCode(-32000);
      response.setErrorMessage((string)e.what());
      handler->getConnection()._send(response.str()+"\r\n");
    }catch(Json::LogicError e){
      cout << e.what()<<endl;
    }

  }

}

void tcp_worker()
{
  Log::logDebug("Started TCP worker");
  while(!TERMNINATE)
  {
    for(int i=0;i<clients.size();i++)
    {
      if(clients.at(i).able())
      {
        if(!clients.at(i).exec())
        {
          /* Error, probably disconnected */
          Log::logDebug((string)"Disconnection connection with: "+clients.at(i).getConnection().getAddress());/* Print IP address of client */
          clients.at(i).close();
          clients.erase(clients.begin()+i); /* Erase from vector */

        }
      }
      else
      {
        Log::logDebug((string)"Closed connection with: "+clients.at(i).getConnection().getAddress());/* Print IP address of client */
        clients.at(i).close();
        clients.erase(clients.begin()+i); /* Erase from vector */
      }
    }
  }
  Log::logDebug("Stopped TCP worker");
}

void printstring(string text)
{
    char chr;
    for(int i=0;i<text.size();i++)
    {
      chr = text.at(i);
      switch (chr)
      {
          case '\n':
              printf("\\n\n");
              break;
          case '\r':
              printf("\\r");
              break;
          case '\t':
              printf("\\t");
              break;
          default:
              if ((chr < 0x20) || (chr > 0x7f)) {
                  printf("\\%03o", (unsigned char)chr);
              } else {
                  printf("%c", chr);
              }
          break;
     }
    }

}
