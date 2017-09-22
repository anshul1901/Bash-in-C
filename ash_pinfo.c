#include "main.h"
#include "stdio.h"
#include "string.h"
#include "fcntl.h"
#include "unistd.h"
#include "sys/wait.h"
#include "sys/types.h"
#include "limits.h"
#include "stdlib.h"

void ash_pinfo(char **args){
  char pid[10];
  if(args[1]==NULL){
    sprintf(pid, "%d", getpid());
  } else {
    strcpy(pid, args[1]);
  }
  char dir[]="/proc/", content[3000];
  char exePath[PATH_MAX +2];
  char symPath[50];
  char **stat;
  strcat(dir, pid);
  strcpy(symPath, dir);
  strcat(dir, "/stat");
  strcat(symPath, "/exe");
  // printf("%s\n", symPath);
  int t = readlink(symPath, exePath, sizeof(exePath));
  if(t == -1){
    strcpy(exePath, "broken link");
  }
  exePath[t] = '\0';
  convertCWD(exePath);
  int fd = open(dir, O_RDONLY);
  if(fd == -1){
    perror("ash");
    return;
  }
  read(fd, content, 250);
  stat = ashGetArgs(content, " \t\r\n\a");
  printf("pid -- %s\nProcess Status -- %s\nVirtual Memory-- %s\nExecutable Path -- %s\n", stat[0], stat[2], stat[23], exePath);
}
