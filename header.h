#ifndef SHELL
#define SHELL

typedef struct pro{
	int index;
	pid_t pid;
	char str[1024];
	int state;
}proc_names;

// typedef struct 
// {
// 	char pname[100];
// 	int state
// }bgprocs;


// bgprocs joblist[1000];
proc_names process_names[40000];
int cs=0;

char curr_proc[256];
pid_t curr_pid;
int num_proc;
#endif