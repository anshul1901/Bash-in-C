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
    printf("\n[%d] exited normally\n", pid);
    bgcount--;
  }
}

void handler2(int sig){
  signal(SIGINT, handler2);
	fflush(stdout);
}

void handler3(int sig){
	int i,index,currpid;
	kill(currpid,20);
	kill(currpid,18);

	for(i=0;i<countfg;i++)
	{
		if(idnumf[i]==currpid)
		{
			index = i;
			break;
		}
	}

	idnum[procnum] = currpid;
	strcpy(pro[procnum],prof[index]);
	procnum++;

}

int ashLaunch(char **args, int bgflag)
{
  int pid, wpid;
  int status;
  signal(SIGCHLD, handler);
  pid = fork();
  if (pid == 0) {
    signal(SIGCHLD, handler2);
    if (execvp(args[0], args) == -1) {
      perror("ash");
    }
    exit(1);
  } else if (pid < 0) {
    perror("ash");
  }
  if (!bgflag) {
    signal(SIGINT, handler2);
    waitpid(pid, &status, WUNTRACED);
  } else {
    bgcount++;
    printf("[%d] %d\n", bgcount, pid);
    waitpid(pid, &status, WNOHANG);
  }
return 1;
}
