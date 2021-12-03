/*
file: smsh2.c
author: 2018117610_moonjunyong
datetime: 2021-11-12 10:30
description:	small-shell version 2
		small shell that supports command line parsing
		and if.. then.. else. fi logic (by calling process() )

compile: 	cc -o smsh2 smsh2.c splitline.c execute.c process.c controlflow.c
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
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
	fprintf(stderr, "Error: %s, %s\n", s1, s1);
	exit(n);
}

/* compile -> result 
moonjunyong@munjun-yong-ui-MacBookPro ch09 % ./smsh2
> grep lp /etc/passwd
_lp:*:26:26:Printing Services:/var/spool/cups:/usr/bin/false
_usbmuxd:*:213:213:iPhone OS Device Helper:/var/db/lockdown:/usr/bin/false
> if grep lp /etc/passwd
_lp:*:26:26:Printing Services:/var/spool/cups:/usr/bin/false
_usbmuxd:*:213:213:iPhone OS Device Helper:/var/db/lockdown:/usr/bin/false
> then
> echo ok
ok
> fi
> if grep pati /etc/passwd
> echo ok
syntax error: then expected
> fi
s yntax error: fi unexpected
> echo ok
ok
> then
syntax error: then unexpected
*/


