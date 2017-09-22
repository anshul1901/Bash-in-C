#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char **ashGetArgs(char *input, char* delim)
{
  int size = 50, i = 0;
  char **tokens = malloc(size * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(input, delim);
  while (token != NULL) {
    tokens[i] = token;
    i++;

    if (i >= size) {
      size += 50;
      tokens = realloc(tokens, size * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, delim);
  }
  tokens[i] = NULL;
  return tokens;
}
