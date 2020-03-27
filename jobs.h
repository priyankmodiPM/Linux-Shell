#include "header.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void jobs()
{
	int i;
	// printf("jobs\n");
	for(i=0;i<40000;i++)
	{
		// printf("jijin");
		if(process_names[i].str[0] != '\0')
		{
			
			// printf("jijij\n");
			printf("[%d] %s [%d] %s\n", process_names[i].index + 1,process_names[i].str,i,process_names[i].state ? "STOPPED" : "RUNNING");
			// printf("[%d] %s [%d] \n", process_names[i].index + 1,process_names[i].str,i);
		}
	}
	return;
}
