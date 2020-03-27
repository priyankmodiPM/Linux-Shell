int pm_execute(char **args, int flag);

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
// #include "header.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "pinfo.h"
#include "exit.h"
#include "ls.h"
#include "pm_launch.h"
#include "header.h"
#include "remind.h"
#include "set_unset_env.h"
#include "jobs.h"
#include "fg.h"


void fg(char ** args)
{
    int job_num = atoi(args[1]);
    if(job_num<=num_proc)
    {
       pid_t job_pid = process_names[job_num].pid;
       printf("continued process %s with pid %d\n",process_names[job_num].str,process_names[job_num].pid);
       for(int i=job_num;i<num_proc;++i)
         process_names[i].pid=process_names[i+1].pid;
       num_proc--;

       kill(job_pid,SIGCONT);
       curr_pid = job_pid;
       strcpy(curr_proc,process_names[job_pid].str);
       strcpy(process_names[job_pid].str,"");
       int wpid,state;
       wpid = waitpid(job_pid, &state, WUNTRACED);
       while(1)
       {
          if (!WIFEXITED(state) && !WIFSIGNALED(state) && !(WIFSTOPPED(state)))
           {
              wpid = waitpid (job_pid, &state, WUNTRACED);
              continue;
           }
          else
           {
             break;
           }
       }
     }
   
}

//changes a stopped background job to a running background job
void bg(char ** args)
{
    int job_num = atoi(args[1]);
    if(job_num<=num_proc)
    {
      pid_t job_pid = process_names[job_num].pid;
      printf("Continued process %s with pid %d\n",process_names[job_num].str,process_names[job_num].pid);
      kill(job_pid,SIGCONT);
    }
}


int pm_execute(char **args, int flag){
	int i;
	if (args[0] == NULL) {
		return 1;
	}

	else if(strcmp(args[0],"echo")==0){
		return echo(args);
	}

	else if(strcmp(args[0],"pwd")==0){
		return pwd(args);
	}

	else if(strcmp(args[0],"cd")==0){
		return cd(args);
	}

	else if(strcmp(args[0],"pinfo")==0){
		return pinfo(args,root);
	}

	else if(strcmp(args[0],"exit")==0){
		return Exit(args);
	}

	else if(strcmp(args[0],"ls")==0){
		lspm(args);
	}

	else if(strcmp(args[0], "remindme")==0){
		remind(args);
	}
	else if(strcmp(args[0], "jobs")==0){
		int pid = fork();
		int status;
		if (pid == 0)
		{	
			// printf("execute\n");
			jobs(args);
			/* code */
		}
		waitpid (pid, &status, WUNTRACED);
	
	}
	else if(strcmp(args[0], "fg")==0){
		fg(args);
	}
	else if(strcmp(args[0], "bg")==0){
		bg(args);
	}

	else if(strcmp(args[0],"setenv")==0 || strcmp(args[0],"unsetenv")==0){
    	set_unset_env(args);
    }
	// else if(strcmp(args[0], "clock")==0){
	// 	pm_clock(args);
	// }
 //    else if(strcmp(args[0],"kjob")==0)
 //    {
	// 	int job_num,signal_num;
 //    	job_num = atoi(args[1]);
 //    	signal_num = atoi(args[2]);
 //    	if(job_num>num_proc)
 //        	fprintf(stderr,"Invalid job number\n");
 //    	else{
 //          	printf("%sKilled process %s with pid %d%s\n",RED,bgproc[bg_proc_pids[job_num]],bg_proc_pids[job_num],DEF);
 //          	kill(bg_proc_pids[job_num],signal_num);
	// 	}
 //    }
	else if(strcmp(args[0],"quit")==0)
	{
		int q,p;
		for(q=0;q<num_proc;q++)
		{
			kill(process_names[q].pid,9);
		}
		p=getpid();
		kill(p,9);
	}
	else if(strcmp(args[0],"overkill")==0)
	{

	  for(int i=1;args[i]!=NULL;++i){
	    int kpid = process_names[i].pid;
	    strcpy(process_names[kpid].str,"");
	    kill(kpid,SIGINT);
	  }
	  num_proc=0;

	}
	// else if(strcmp(args[0],"fg")==0 || strcmp(args[0],"bg")==0)
	// {
	// 	fb(output);
	// }
	else
		return pm_launch(args);
}