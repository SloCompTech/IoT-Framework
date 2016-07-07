#define OS_LINUX

#include <iostream>
#include <csignal>
#include <cstdlib>

#include <TCPServer/TCPServer.h>
#include <TCPServer/TCPServerConnection.h>
#include <ProcessManip/ProcessManip.h>
#include <Log/Log.h>

//Global
bool TERMNINATE = false;//If true loops must end
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
    TCPServerConnection conn = server._accept();
    if(!conn.isValid())
      continue;

    Log::logDebug((string)"Got connection from: "+conn.getAddress());/* Print IP address of client */

    conn._send("Hello you there, bye :)");
    conn._close();

    Log::logDebug((string)"Closed connection with: "+conn.getAddress());/* Print IP address of client */


  }
  server.setBlocking(true);

  //Dispose
  Log::logDebug("Stopping ...");
  server._close();

  Log::logDebug("Closed");
  return 0;
}

void terminate(int sig)
{
  //Change global value to true
  TERMNINATE = true;
}
