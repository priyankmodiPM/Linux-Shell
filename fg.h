#include"header.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/utsname.h>
#include<pwd.h>

void sigHandle()
{
  int f,s;
  f=waitpid(-1,&s,WNOHANG);
  if(f>0)
  {
    if(WIFEXITED(s)==1)
    {
      printf("\nprocess with pid %d exited normally\n",f);
    }
    else if(WIFSIGNALED(s)==1)
    {
      printf("\nProcess with pid %d did not exit normally\n",f);
    }
  }
}
void fb(char **args)
{
  int b;
  printf("%d\n",cs );
  if(args[1]==NULL)
  printf("Error!");
  else
  {
    if(atoi(args[1])>cs)
    printf("Error!!");
    else
    {
      if(strcmp(args[0],"fg")==0)
      waitpid(process_names[atoi(args[1])-1].pid,&b,WCONTINUED);
      else if(strcmp(args[0],"bg")==0)
      {
        kill(process_names[atoi(args[1])-1].pid,SIGCONT);
        process_names[atoi(args[1])-1].state=0;
      }
    }
  }
}

void fbg(char** args)
{

  int pid=fork(),f=0,i;
  for(i = 0 ; args[i]!=NULL;i++);
  if(strcmp(args[i-1],"&")!=0)
  f=1;
  if(strcmp(args[i-1],"&")==0)
  args[--i]=NULL;
  if(pid==0)
  {
    redirect(args,i);

    if(execvp(args[0],args) == -1)
    {
      perror("error");
    }
  }
  else if(pid<0)
  {
    perror("error");
  }
  else if(pid>0)
  {
  if(f==1)
  {
    wait(NULL);
  }
  else {
    process_names[cs].pid=pid;
    strcpy(process_names[cs].str,args[0]);
    cs+=1;
   
  }
}
  signal(SIGCHLD,sigHandle);
}
