#include "main.h"
#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int ash_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "ash: invalid syntax\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("ash");
    }
  }
  return 1;
}

int ash_pwd() {
  char cwd[100];
  getcwd(cwd, 200);
  printf("%s\n", cwd);
  return 1;
}

int ash_echo(char **args) {
  int i;
  if(args[1][0] == 34){
    for(i=1; ; i++){
      printf("%s ", args[i]);
      if(args[i][strlen(args[i])-1] == 34)
        break;
    }
    printf("\n");
  } else {
    printf("%s\n", args[1]);
  }
  return 1;
}

int ashExecute(char **args, int bgflag) {
    for (int i = 0; args[i] != NULL; i++) {
    if ((strcmp(args[i], ">")) == 0 || (strcmp(args[i], "<")) == 0 || (strcmp(args[i], ">>")) == 0) {
      ash_redirection(args);
      return 1;
    }
  }
  if (args[0] == NULL) {
    return 1;
  } else if(strcmp(args[0], "quit")==0){
    exit(0);
  } else if (strcmp(args[0], "cd")==0) {
    ash_cd(args);
  } else if (strcmp(args[0], "pwd")==0) {
    ash_pwd();
  } else if (strcmp(args[0], "echo")==0) {
    ash_echo(args);
  } else if(strcmp(args[0], "pinfo")==0) {
    ash_pinfo(args);
  } else if(strcmp(args[0], "ls")==0 || strcmp(args[0], "l")==0) {
    ash_ls(args);
  } else {
    return ashLaunch(args, bgflag);
  }
  return 1;
}
