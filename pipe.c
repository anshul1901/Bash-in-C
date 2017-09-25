#include "main.h"
#include <unistd.h>
#include "stdio.h"

struct command {
  char **argv;
};

void spawn_proc (int in, int out, struct command *cmd) {
  pid_t pid;
  if ((pid = fork ()) == 0) {
      if (in != 0) {
          dup2(in, 0);
          close(in);
      }
      if (out != 1) {
          dup2 (out, 1);
          close (out);
      }
      execvp (cmd->argv [0], (char * const *)cmd->argv);
  }
}

int fork_pipes (int n, struct command *cmd) {
  int i;
  int in, fd [2];
  in = 0;
  for (i = 0; i < n - 1; ++i) {
      pipe (fd);
      spawn_proc (in, fd [1], cmd + i);
      close (fd [1]);
      in = fd [0];
  }
  if (in != 0)
    dup2 (in, 0);
  execvp (cmd [i].argv [0], (char * const *)cmd [i].argv);
}

void piping (char **args) {
  int saved_in = dup(0);
  int saved_out = dup(1);
  struct command cmd[100];
  int i;
  for(i=0; args[i]!=NULL; i++){
    (cmd+i)->argv = (char**)ashGetArgs(args[i], " \t\r\n\a");
  }
  fork_pipes(i, cmd);
  dup2(saved_in, 0);
  close(saved_in);
  dup2(saved_out, 1);
  close(saved_out);
}
