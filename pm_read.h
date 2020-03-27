char *pm_read();

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

// extern char *root;

char *pm_read() {

  int index = 0;
  char *inp = malloc(sizeof(char) * 1000), c;
  
  if (!inp) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }
  
  //read untill the end of the string 
  while(1) {
    c = getchar();
    if (c == EOF || c == '\n') {
      inp[index] = '\0';
      return inp;
    }
    else inp[index++] = c;
  }
}