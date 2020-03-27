char* returnPath (char* cwd);
void printPrompt (char *root);
void main_loop();

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pm_read.h"
#include "pm_split.h"
#include "header.h"
#include "pm_execute.h"

// typedef struct pro{
// 	int index;
// 	char str[1024];
// }proc_names;
void checkctrl_C(int sig)
{
  pid_t check_pid = getpid();

	if(curr_pid > 0)
		kill(curr_pid, SIGINT);
	signal(SIGINT, checkctrl_C);
  curr_pid=-1;
}

void checkctrl_Z(int sig)
{
	if(curr_pid > 0)
	{
		kill(curr_pid, SIGTTIN);
		kill(curr_pid, SIGTSTP);
    num_proc++;
    process_names[num_proc].pid = curr_pid;
    strcpy(process_names[curr_pid].str,curr_proc);
	  printf("+[%d] %d %s\n",num_proc,curr_pid,process_names[curr_pid].str);
	}
	signal(SIGTSTP, checkctrl_Z);
}

void childHandler(int sig)
{
  int check;
  for(int p=1;p<=num_proc;)
  {
    int ret_pid = waitpid(process_names[p].pid,&check,WNOHANG|WUNTRACED);
    if(process_names[p].pid == ret_pid)// process terminated
    {
      if(WIFEXITED(check))
         fprintf("%sBackground process: %s and pid %d exited normally with exit status %d%s\n",process_names[ret_pid].str,ret_pid,WEXITSTATUS(check));
      else if (WIFSIGNALED(check))
         fprintf("%sBackground process: %s and pid %d exited abnormally with exit status %d%s\n",process_names[ret_pid].str,ret_pid,WTERMSIG(check));
      // delete that process from storage
      for(int i=p;i<num_proc;++i)
         process_names[i].pid=process_names[i+1].pid;
      strcpy(process_names[ret_pid].str,"");
    //  reduce the number of background processes
      num_proc--;
    }
    else
      p++;
  }
 signal(SIGCHLD, childHandler);
}


extern char root[100];
// proc_names process_names[40000];

void getPrompt() {
	char *username = getenv("USER");
	char *hostname = malloc(30*sizeof(char));
	char *currdir = malloc(100*sizeof(char)); 
	int i;
	getcwd(currdir,100);
	int currlen = strlen(currdir);
	int homelen = strlen(root);
	currdir[currlen++] = 47; 
	gethostname(hostname,30);
	if (currlen >= homelen) {
		int flag = 0;
		for(i=0;i<homelen;i++) {
			if(currdir[i] != root[i]) {
				flag = 1;
			}
		}
		int j = 0;
		if (flag == 0) {
			currdir[j++] = '~';
			currdir[j++] = '/';
			for(i=homelen;i<currlen;i++) currdir[j++] = currdir[i];
			while(j<currlen) currdir[j++] = 0;
		}
	}	
	printf("<%s@%s:%s> ",username,hostname,currdir);
	free(hostname);
	free(currdir);
}

//  void sig_handler(int signo)
//   {
//     if(signo==SIGINT)
//     {
//       fprintf(stderr,"\n");
//       getprompt();
//     }

// }

void main_loop(){
	// char home[1005];
	// getcwd(home,1000);
	// char root[1005];
	getcwd(root,1000);
	root[strlen(root)] = 47;

	char *line;
	char **args;
	
	int status;
	signal(SIGTSTP, checkctrl_Z);
  	signal(SIGINT, checkctrl_C);
	signal(SIGCHLD, childHandler);

	do{
		int state;
		pid_t pid;
		curr_pid = -67;
		while((pid = waitpid(-1,&status,WNOHANG)) > 0)
		{	
			if (WIFEXITED(status) && process_names[pid].str != NULL)
			{
				printf("%s with pid %d exited normally\n",process_names[pid].str,pid);
    		}
    	}
		// printPrompt(root);
		getPrompt();
		line = pm_read();
    
    	char *prompt;
    
    //splitting the command on the basis of the semicolon
    	while(line) {
      		int flag = 0;
      		prompt = strsep(&line,";");
      		args = pm_split(prompt);
      		int len = 0;
      
      	while(args[len] != NULL)
			len++;
      
      // 	if(len > 1 && args[len-1][0] == '&') { 	
      // 	//printf("check\n");
      // 		flag = 1;
      // 		args[len-1] = NULL;
     	// }

      	status = pm_execute(args, flag);
      
      	if(status == 0)
			return; //user_input = read_input();
		}

		free(line);
		free(args);

	}while(status);

	return;
}