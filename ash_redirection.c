#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "errno.h"
#include "sys/types.h"
#include "fcntl.h"


void redirection(char **args)
{
	int in;
	int out;
  char *infile, *outfile;
	size_t got;

  for (int i = 0; args[i] != NULL; i++) {
    if (strcmp(args[i], "<") == 0)
      infile = args[i];
    else if (strcmp(args[i], ">") == 0)
      outfile = args[i];
  }
	char buffer[1024];
	in = open (infile, O_RDONLY);
	out = open (outfile, O_TRUNC | O_CREAT | O_WRONLY, 0666);
	if ((in <= 0) || (out <= 0))
	{
		perror("ash");
		exit (errno);
	}
	dup2 (in, 0);
	dup2 (out, 1);
	close (in);
	close (out);
	while (1)
	{
		got = fread (buffer, 1, 1024, stdin);
		if (got <=0) break;
		fwrite (buffer, got, 1, stdout);
	}
}
