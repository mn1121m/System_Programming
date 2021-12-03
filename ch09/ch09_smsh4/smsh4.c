/*
file: smsh4.c
author: 2018117610_moonjunyong
datetime: 2021-11-20 1:00
description:	small-shell version 4
		small shell that supports command line parsing
		and if.. then.. else. fi logic (by calling process())
*/
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include 	<sys/wait.h>
#include	"smsh.h"
#include 	"varlib.h"

#define DFL_PROMPT	"@ "

int main()
{
	char	*cmdline, *prompt, **arglist;
	int	result, process(char **);
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
    extern char **environ;
	VLenviron2table(environ);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
	fprintf(stderr, "Error: %s, %s\n", s1, s1);
	exit(n);
}




