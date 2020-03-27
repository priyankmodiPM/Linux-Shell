int cd (char** args);

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
extern char root[100];

int cd (char** args) {
    if (args[1] == NULL)
        return 1;
    else if (strcmp(args[1],"~")==0){
        chdir(root);
    }
    else if (chdir(args[1]) != 0)
        perror("error");
    return 1;
}