#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/utsname.h>
#include<pwd.h>
#include<sys/stat.h>
#include<fcntl.h>

void set_unset_env(char** args)
{
  if(strcmp(args[0],"setenv")==0)
  {
  	// setenv(args[1],args[2],1);
  	// printf("Sriven is a dick\n");
    int n = setenv(args[1],args[2],1);
  	// printf("Sriven is a dick\n");
    
    printf("%s set to %s\n", args[1], args[2]);
    if(n<0)
    	perror("shell");
    return 1;
  }
  else if(strcmp(args[0],"unsetenv")==0)
  {
    int t = unsetenv(args[1]);
    printf("%s unset\n", args[1]);

    if(t<0)
    	perror("shell");
    return 1;
  }
}
