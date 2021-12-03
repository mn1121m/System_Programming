/*
file: smsh3.c
author: 2018117610_moonjunyong
datetime: 2021-11-12 10:30
description:	small-shell version 3
		small shell that supports command line parsing
		and if.. then.. else. fi logic (by calling process() )

compile: 	cc -o smsh3 smsh2.c splitline.c execute.c process2.c \
controlflow.c  builtin.c varlib.c
			./smsh2

*/
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include 	<sys/wait.h>
#include	"smsh.h"

#define DFL_PROMPT	"> "

int main()
{
	char	*cmdline, *prompt, **arglist;
	int		result, process(char **);
	void	setup();

	prompt	= DFL_PROMPT;
	setup();
	
	while( (cmdline = next_cmd(prompt, stdin)) != NULL ) {
		if( (arglist = splitline(cmdline)) != NULL ) {
			result = process(arglist);
			freelist(arglist);
		}
		free(cmdline);
	}
	return 0;

}

void setup()
/*	purpose: initialize shell
* 	returns: nothing. calls fatal() if trouble
*/
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
	fprintf(stderr, "Error: %s, %s\n", s1, s1);
	exit(n);
}

/* compile && result
------compile-------------
cc -o smsh3 smsh2.c splitline.c execute.c process2.c controlflow.c \builtin.c varlib.c
./smsh3

------result--------------
> set
> day=monday
> temp=75
> TZ=CST6CDT
> x.y=z
cannot execute command: No such file or directory
> set
    day=monday
    temp=75
    TZ=CST6CDT
> date
2021년 12월  3일 금요일 21시 43분 54초 KST
> echo $temp, $day
$temp, $day
-------------------------------
*/