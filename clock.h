#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#define Delimiters " \t\r\n\a"

void pm_clock(char **args){
	char rtc_path[100];
	char file_read[256];
	char **arg;

	strcpy(rtc_path, "/proc/driver/rtc");
	FILE *status = fopen(rtc_path, "r");
	if(status==NULL){
		fprintf(stderr, "RTC log files not found\n");
		return 1;
	}
	else{
		int t = 0;
		while(t < atoi(args[4])){
			//printf("check\n");
			//printf("%s\n", status);

			FILE *status = fopen(rtc_path, "r");
			fgets(file_read,256,status);

			//printf("%s\n", arg);

			arg = pm_split(file_read);
			printf("%s", arg[2]);

			fgets(file_read,256,status);
			arg = pm_split(file_read);

			printf("%s\n",arg[2]);

			sleep(atoi(args[2]));

			fclose(status);
			
			t = atoi(args[2]);
		}
	}
	return 1;
}