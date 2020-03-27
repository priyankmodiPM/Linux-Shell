#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "header.h"
#include <string.h>

#include "main_loop.h"

#define Delimiters " \t\r\n\a"

char root[100];

int main(int argc, char **argv ){
	// char root = malloc(1000 * sizeof(char));

	// printf("1.%ld\n", time(NULL));
	getcwd(root,100);
	main_loop();
	return EXIT_SUCCESS;
}