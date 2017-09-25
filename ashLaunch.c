#include "main.h"
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "sys/wait.h"
#include "sys/types.h"
#define ANSI_COLOR_RED    "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void handler(int sig)
{
  pid_t pid;
  pid = wait(NULL);
  if(pid!=-1){
    printf("\n[%d] done.\n", pid);
    bgcount--;
  }
}

int ashLaunch(char **args, int bgflag)
{
  int pid, wpid;
  int status;
  signal(SIGCHLD, handler);
  pid = fork();
  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("ash");
    }
    exit(1);
  } else if (pid < 0) {
    perror("ash");
  }
  if (!bgflag) {
    waitpid(pid, &status, WUNTRACED);
  } else {
    bgcount++;
    printf("[%d] %d\n", bgcount, pid);
    waitpid(pid, &status, WNOHANG);
  }
return 1;
}
