int echo(char **args);

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int echo(char **args) { 
  
  int ind = 1, start = 1, end;
  
  while(args[ind] != NULL) {
    printf("%s ", args[ind]);
    ind++;
  }

  printf("\n");
  
  return 1;

//   int i;
//   for(i=1;i<nargs;i++)
//   {
//       if(args[i]==NULL)
//         break;

//       // if environment variable
//       if(args[i][0]=='$')
//       {
//         char *env ;
//         env = getenv(args[i]+1);
//         if(env!=NULL)
//             fprintf(stdout,"%s ",env);
//       }
//       else
//       {
//         int j=0;
//         while(args[i][j]!='\0')
//         {
//           if(args[i][j] != '\"' && args[i][j]!= '\'' )
//               fprintf(stdout,"%c",args[i][j]);
//           j++;
//         }
//         fprintf(stdout," ");
//       }
//   }
//    fprintf(stdout,"\n");
// return 1;



}

// int echo(char **args){
// 	int ind = 1, start = 1, end;
// 	if(args[1][0] == "'"){
// 		while(args[ind] != "'"){
// 			printf("%s", args[ind]);
// 			ind++;
// 		}
// 	}

// 	if(args[1][1] == "$"){
// 		//check if env var exits
// 		//print value of var
// 	}

// 	if(args[2][0] == ">" || args[3][0] == ">"){
// 		//redirect
// 	}

// 	if(args[2][0] == "|" || args[3][0] == "|"){
// 		//pipe
// 	}
// }