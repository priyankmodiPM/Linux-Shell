ALL functionality expect clock has been implemented(clock sowed segmentation fault during testing[not yet resolved])
remindme bonus implemented

to compile code, do a make and then ./msh



the main.c file executes the main function and initiates the main loop

THe commands are then split first to get different commands separated by semicolons and are then parsed for arguments - main_loop

once the commands are parsed, the execute function is called which checks if the command is a builtin command or not - pm_execute

if, it is builtin, the respective functions are called(eg ls.h, cd.h etc), else pm_launch is called for all other commands

here, the first check is for bg and fg processes and the program executes accordingly, printing messages on exiting the process which is printed using the pid of the process