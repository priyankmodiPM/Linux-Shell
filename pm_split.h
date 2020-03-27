char **pm_split(char *line);

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// #include "header.h"

#define Delimiters " \t\r\n\a"

char **pm_split(char *line) {
 
  //splitting a "single command" into the command name and the flags
  int status,ind,pos;
  status = ind = pos = 1;
  pos -= 1;
  char **tokens = malloc(100* sizeof(char*)), *token;
    
  if (!tokens) {
    fprintf(stderr, "allocation error\n");
    exit(EXIT_FAILURE);
  }
    
  token = strtok(line, Delimiters);
    
  while(token) {
    tokens[pos++] = token;
    token = strtok(NULL, Delimiters);
  }
  
  //printf("position hai : %d\n", position);
  tokens[pos] = NULL;
  free(token);
    
  return tokens;
}