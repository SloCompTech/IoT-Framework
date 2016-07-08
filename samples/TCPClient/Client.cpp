#define OS_LINUX

#include <iostream>
#include <csignal>
#include <cstdlib>

#include <TCPClient/TCPClient.h>


#include <Log/Log.h>

//Global
bool TERMNINATE = false;//If true loops must end
const string ADDRESS = "127.0.0.1";
const int PORT = 8822;

//Proto
void terminate(int sig);

using namespace std;

int main(int argc,char *argv[])
{
  //Add Terminate handler
  signal(SIGINT,terminate);

  //Load configuration
  Log::logDebug("Starting ...");

  //Init

  //Init modules

  //Main
  Log::logDebug("Running");
  TCPClient client;

  if(!client._connect(ADDRESS,PORT))
    return 1;

  if(!client.isValid())
    return 2;

  Log::logDebug((string)"Connected to: "+client.getAddress());/* Print IP address of server */


  client.setBlocking(false);/* accept returns invalid socket if no connection */
  Log::logDebug("Waiting for message ...");
  string message = "";
  while(!TERMNINATE)
  {
    message = client._receive();
    if(message!="")
        break;

  }
  client.setBlocking(true);

  Log::logDebug((string)"Message: "+message); /* Prints out received message */
  //Dispose
  Log::logDebug("Disconnecting ...");
  client._close();

  Log::logDebug("Closed");
  return 0;
}

void terminate(int sig)
{
  //Change global value to true
  TERMNINATE = true;
}
