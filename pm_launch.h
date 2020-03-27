#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/utsname.h>
#include<pwd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "header.h"
#include "redirect.h"
#include "pipe.h"


// int checkBackground(char **args)
// {
//     int i,j;
//     for(i=0; args[i] != NULL; i++)
//     {
//         if(strcmp(args[i],"&")==0)
//             return i;
//     }
//     return 0;      
// }


int pm_launch (char **args) {
    
    int i,j;
    num_proc = 0;
    // int background=checkBackground(args);
    int background=0;
    int redirect_flag = 0, pipe_flag = 0;

    for (i = 0;args[i] != NULL;i++) {
        // for (j = 0;args[i][j] != '\0'; j++) {
            
            if (strcmp(args[i],"|")==0)
                pipe_flag = 1;
        // }    
            else if (strcmp(args[i],">")==0 || strcmp(args[i],"<") == 0){
                redirect_flag = 1;
                // printf("redirect flag set to %d", redirect_flag);
            }
            else if (strcmp(args[i],"&")==0) 
               {
                background = 1;
                args[i] = NULL;
                num_proc++;
                // fprintf(stdout,"%s\n","Hi" );
               } 
        // break;
    }


if (redirect_flag) {
        return redirect(args, i);   
    }


if (pipe_flag){
    return pipe_func(args);
}

    pid_t pid, wpid;
    int status;
    pid = fork();
    
    // if (pipe_flag) {
    //     piping(args);
    //     return 1;
    // }
    

    if (pid < 0) {
        perror("ERROR!");
    }

    else if(!pid) {
        if ( execvp(args[0], args) == -1)
            perror("ERROR!");
        exit(EXIT_FAILURE);
    }

    // printf("background = %d\n", background);
    if(!background) {
    // printf("insdide foreground background = %d\n", background);
        strcpy(curr_proc,args[0]);
        curr_pid = pid;
        // strcpy(process_names[pid],args[0]);

        wpid = waitpid (pid, &status, WUNTRACED);
        for (i = 0;; i++) {
        if (!WIFEXITED(status) && !WIFSIGNALED(status)) {
            wpid = waitpid (pid, &status, WUNTRACED);
            continue;
            }
        break;
        }
    }
    strcpy(process_names[pid].str,args[0]);
    // cs ++;
    return 1;
}
