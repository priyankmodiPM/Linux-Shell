#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int fd1,fd2,fd3;
char in[100],out[100],outdir[100];


void func_in(){
	//open file
	fd1 = open(in,O_RDONLY,0);

	//if  error
	if (fd1<0){
		perror("Could not open input file"); 
		exit(0);
	}

	dup2(fd1,0);
	close(fd1);
}


void func_out(){
	//open file
	fd2 = open (out, O_WRONLY | O_CREAT, 0666);

	//if error
	if(fd2<0){
	   perror("Could not open the output file");
	   exit(0);
	}

  	dup2(fd2,1);
	close(fd2);
}


void func_outdir(){
	fd3 = open (outdir, O_WRONLY | O_CREAT | O_APPEND , 0666);
  	if(fd3<0){
    	perror("Could not open the output file");
    	exit(0);
  	}

  	dup2(fd3,1);
  	close(fd3);
}


int redirect(char **args, int num)
{
	int r = 0,pid,flag1=0,flag2=0,flag3=0;
	args[num] = NULL;

	pid = fork();

	if(pid==0){
		for (int i=0;i<num;i++)
		{
			if (strcmp(args[i],"<")==0)
			{
				args[i] = NULL;
				flag1 = 1;
				strcpy(in,args[i+1]);
			}
			
			if (args[i]!=NULL)
			{
				if (strcmp(args[i],">")==0)
				{
					args[i] = NULL;
					flag2 = 1;
					strcpy(out,args[i+1]);
				}
			}

			if (args[i]!=NULL)
			{
				if (strcmp(args[i],">>")==0)
				{
					args[i] = NULL;
					flag3 = 1;
					strcpy(outdir,args[i+1]);
				}
			}

		}

		if(flag1 == 1)
			func_in();
		if(flag2 == 1)
			func_out();
		if(flag3 == 1)
			func_outdir();

		// if (execvp(args[0],args)<0){
		// 	r=1; 
		// 	printf("%s: Command doesn't exist\n", args[0]);
		// }
	}
	// else
	// 	wait(NULL);
	
	// if (r!=1)
	// 	printf("%s with process id: %d exited normally\n",args[0],pid);	

	return 1;
}
