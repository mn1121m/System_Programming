/*
file: smsh1.c
author: 2018117610_moonjunyong
datetime: 2021-11-12 10:30
description:	small-shell version 1
		first really useful version after prompting shel
		this one parses the command line into strings
		uses fork, exec, wait, and ignores signals
*/
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	"smsh.h"

#define DFL_PROMPT	"> "

int main()
{
	char	*cmdline, *prompt, **arglist;
	int	result;
	void	setup();

	prompt	= DFL_PROMPT;
	setup();
	
	while( (cmdline = next_cmd(prompt, stdin) ) != NULL) {
		if( (arglist = splitline(cmdline)) != NULL ) {
			result = execute(arglist);
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




