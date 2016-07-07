#ifndef LIB_PROCESSMANIP
#define LIB_PROCESSMANIP

#include <cstdlib>
#include <cstdio>
#include <sys/wait.h>
#include <csignal>
#include <errno.h>

namespace ProcessManip
{
  extern void handle_sigchld(int sig);
  extern void cleanProcess();
}

#endif
