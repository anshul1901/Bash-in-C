#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "errno.h"
#include "sys/types.h"
#include "fcntl.h"
#include "sys/wait.h"


int ash_redirection(char **args)
{
	int in;
	int out;
  char *infile, *outfile;
  int pid;
  int flagin = 0, flagout = 0, flagout_append= 0;
  int i;

  for (i = 1; args[i] != NULL; i++) {
    if (strcmp(args[i], "<") == 0) {
      infile = args[i + 1];
      args[i] = NULL;
      args[i + 1] = NULL;
      flagin = 1;
      i++;
    }
    else if (strcmp(args[i], ">") == 0) {
      outfile = args[i + 1];
      args[i] = NULL;
      args[i + 1] = NULL;
      flagout = 1;
      i++;
    }
    else if (strcmp(args[i], ">>") == 0) {
      outfile = args[i + 1];
      args[i] = NULL;
      args[i + 1] = NULL;
      flagout_append = 1;
      i++;
    }
  }

  int saved_in = dup(0);
  int saved_out = dup(1);
  if (flagin) {
	  in = open (infile, O_RDONLY);
    dup2 (in, 0);
    close (in);
  }
  if (flagout) {
	  out = open (outfile, O_TRUNC | O_CREAT | O_WRONLY, 0644);
    dup2 (out, 1);
    close (out);
  }
  if (flagout_append) {
	  out = open (outfile, O_APPEND | O_CREAT | O_WRONLY, 0644);
    dup2 (out, 1);
    close (out);
  }
	if (( flagin && in <= 0) || (flagout && out <= 0) || (flagout_append && out <= 0)) {
		perror("ash");
		exit (errno);
	}
  pid = fork();
  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("ash");
    }
    exit(1);
  }
  dup2(saved_out, 1);
  close(saved_out);
  dup2(saved_in, 0);
  close(saved_in);

  return 0;
}
