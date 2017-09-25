#include "main.h"
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
#include "signal.h"
#define ANSI_COLOR_RED    "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void ashLoop() {
  char *input, **args, **argz;
  int status, i=0;
  int bgflag, j;
  signal(SIGINT, handler2);
  do {
    start:
    getcwd(cwd, 80);
    if(i==0){
      strcpy(HOME, cwd);
      i=1;
      bgcount = 0;
    }
    cuserid(user);
    gethostname(hostname, 200);
    if(strcmp(cwd, HOME)==0){
      strcpy(displayCWD,"~");
    } else {
      strcpy(displayCWD, cwd);
      convertCWD(displayCWD);
    }
    printf(ANSI_COLOR_BLUE "<%s@%s:%s> " ANSI_COLOR_RESET, user, hostname, displayCWD);
    input = ashRead();
    argz = ashGetArgs(input, ";");
    bgflag = 0;
    for (int i = 0; argz[i] != NULL; i++) {
      bgflag = 0;
      args = ashGetArgs(argz[i], " \t\r\n\a");
      j = 0;
      // printf("test\n");
      if(args[0]==NULL)
        continue;
        // printf("%s\n", "yo NULL m8");
      while(args[j]!=NULL) {
        j++;
      }
      --j;
      if (args[j][strlen(args[j])-1] == '&'){
        bgflag=1;
        args[j][strlen(args[j])-1] = ' ';
      }
      status = ashExecute(args, bgflag);
      free(args);
    }
    free(input);
  } while (1);

}
