#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include "pm_read.h"
// #include "pm_split.h"
// #include "pm_execute.h"

extern char root[100];

char pinfo(char **args, char *root)
{
	char procpath[1000+1];
	int count=0;
	int pid; 
	char status; 
	char name[20];
	strcpy(procpath, "/proc/");

	if(args[1])
		strcat(procpath, args[1]);
	else
		strcat(procpath, "self");

	char statpath[1000+1];
	strcpy(statpath, procpath);
	strcat(statpath, "/stat");

	FILE *stat = fopen(statpath, "r");
	if(stat == NULL){
		perror("shell");
		return 0;
	}
	char msg[100];
	fscanf(stat, "%d", &pid);
	fscanf(stat, "%s", name);
	fscanf(stat, "%c", &status);

	if(root == NULL){
		return status;
	}

	fprintf(stdout, "pid: %d\n", pid);
	fprintf(stdout, "Process Status: %c\n", status);
	fclose(stat);

	strcpy(statpath, procpath); 
	strcat(statpath, "/statm");
	FILE *mem = fopen(statpath, "r");
	if(mem == NULL){
		perror("error");
		return 0;
	}
	int size;
	fscanf(mem, "%d", &size);
	fprintf(stdout, "Memory: %d\n", size);
	fclose(mem);

	char exepath[1000+1];
	strcpy(statpath, procpath);
	strcat(statpath, "/exe");

	readlink(statpath, exepath, sizeof(exepath));
	if(count)
	{
		perror("error");
	}

	char *ret;

	ret = strstr(exepath, root);
	int baseL = strlen(root);

	char relpath[1000+1];
	if(ret!=NULL)
	{
		relpath[0] = '~'; relpath[1] = '\0';
		strcat(relpath, (const char *)&exepath[baseL]);
	}
	else
	{
		strcpy(relpath, exepath);
		relpath[strlen(exepath)] = '\0';
	}

	int i = 0;
	while(exepath[i])
		exepath[i++] = '\0';

	fprintf(stdout, "Executable Path: %s\n", relpath);
	return status;
}