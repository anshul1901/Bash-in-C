#include "unistd.h"
#include "stdio.h"
#include "main.h"

char *ashRead() {
  char *input = NULL;
  ssize_t size = 0;
  getline(&input, &size, stdin);
  return input;
}
