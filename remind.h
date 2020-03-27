#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#define rep(i, a, b) for(i = a; i != b; i++) 
#define rev(j, a, b) for(j = a; j >= b; j--) 


void remind(char **args){
	int j;
	pid_t pid;
	int t = atoi(args[1]);
	pid = fork();

	if(pid<0){
		perror("ERROR");
		return;
	}

	if(pid == 0){
		if(!atoi(args[1])){
			perror("ERROR, expected number of seconds");
			exit(0);
			return;
		}
	
		sleep(t);
		for(int i=2;args[i] != NULL;i++)
			printf("%s\n", args[i]);
	}
}
