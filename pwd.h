int pwd (char** args);

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

int pwd (char** args) {
    char *curr_dir = (char *)malloc(1000*sizeof(char)); 
    getcwd(curr_dir, 1000); 
    printf("%s\n", curr_dir);
    free(curr_dir);
    return 1;
}