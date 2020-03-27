#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>

// void func1(){
// 	dup2(p[0],0);
// }

// void func2(){
// 	dup2(p[1],0);
// }

// void func3(){
// 	dup2(p[0],1);
// }

// void func4(){
// 	dup2(p[1],1);
// }
// void func5(){
// 	dup2(q[0],0);
// }

// void func6(){
// 	dup2(q[1],0);
// }

// void func7(){
// 	dup2(q[0],1);
// }

// void func8(){
// 	dup2(q[1],1);
// }
int pipe_func (char ** args){

	pid_t pid;
	int status;
	int p[2],q[2],i=0,j=0,k=0,flag1,end=0,fd1,fd2,fd3,m=0,count=0,last=0;

	char *sym[100];
	char * r = args[0];
	//Count the no. of command line arguments in piping
	while(r!=NULL){
		if (strncmp(args[m],"|",1)==0){
			count++;
		}
		m++;
		r = args[m];
	}
	count++;

	last =count -1 ;

	//The main loop for piping
	while(args[j]!=NULL &&  end!=1){
		k = 0;
		char * d = args[j];

		for(k=0;(strcmp(d,"|")!=0);k++){
			sym[k]=d;
			j++;
			d = args[j];
			if(d == NULL){
				end = 1;
				k++;
				break;
			}
		}

		sym[k] = NULL;
		j++;

		if (i%2 != 0)
			pipe(p);
		else
			pipe(q);

		pid = fork();

		//Error
		if(pid < 0)
			perror("Unable to fork the process");


		//child process
		if (pid == 0){

			if (i==0){
				// func8();
				dup2(q[1],1);
			}
			else if (i==last){
				if(count%2==0){
				dup2(q[0],0);
					// func5();
				}
				else{
					// func1();
				dup2(p[0],0);
				}
			}

			else{
				if(i%2==0){
					// func1();
					dup2(p[0],0);

					dup2(q[1],1);
					// func8();
				}
				else{
					dup2(q[0],0);
					// func5();
					dup2(p[1],1);
					// func4();
			}
			}
			if (execvp(sym[0],sym)==-1){
				kill(getpid(),SIGTERM);
			}
		}

		if(i==0){
			close(q[1]);
		}

		else if(i==last){
			if(i%2==0){
				close(q[0]);
			}
			else{
				close(p[0]);
			}
		}

		else{
			if(i%2==0){
				close(p[0]);
				close(q[1]);
			}
			else{
				close(q[0]);
				close(p[1]);
			}
		}

		waitpid(pid,NULL,0);
		i++;


	}

	return 1;
}