/*

file: execute2.c - code used by small shell to execute commands
author: 2018117610_moonjunyong
datetime: 2021-11-20 1:00
description:	purpose:	run a program passing it arguments
		return: 	status returned via wait, or -1 on error
		errors:		-1 on fork() or wait() errors

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include	"varlib.h"

extern char **environ;

int execute(char *argv[])
{
	int 	pid;
	int 	child_info = -1;
	
	if( argv[0] == NULL)
		return 0;
	if( (pid = fork()) == -1)
		perror("fork");
	else if (pid == 0) {
	    environ = VLtable2environ();	/* new line */
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execvp(argv[0], argv);
		perror("cannot execute command");
		exit(1);
	}
	else {
		if( wait(&child_info) == -1)
			perror("wait");
	}
	return child_info;
}
/* compile

cc -o smsh4 smsh4.c splitline.c execute2.c process2.c controlflow.c builtin.c varlib.c
./smsh4
*/

/* result

@ date
2021년 12월  3일 금요일 23시 30분 03초 KST
@ TZ=PST8PDT
@ export TZ
@ date
2021년 12월  3일 금요일 06시 30분 20초 PST
@ 
*/