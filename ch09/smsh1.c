/*
file: smsh1.c
author: 2018117610_moonjunyong
datetime: 2021-11-12 10:30
description:	small-shell version 1
		first really useful version after prompting shel
		this one parses the command line into strings
		uses fork, exec, wait, and ignores signals
		compile: cc smsh1.c splitline.c execute.c -o smsh1
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
	int		result;
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
/* compile -> result
moonjunyong@munjun-yong-ui-MacBookPro ch09 % cc smsh1.c splitline.c execute.c -o smsh1
moonjunyong@munjun-yong-ui-MacBookPro ch09 % ./smsh1


> ls -al /tmp
lrwxr-xr-x@ 1 root  wheel  11 10 18 12:30 /tmp -> private/tmp  
> ps -f
  UID   PID  PPID   C STIME   TTY           TIME CMD
  501 63259 15758   0 화01PM ttys000    0:00.11 /bin/zsh -l
  501 64300 15758   0 화02PM ttys001    0:00.03 /bin/zsh -l
  501 65894 15758   0 화06PM ttys002    0:00.02 /bin/zsh -l
  501 69058 15758   0  4:07PM ttys004    0:00.04 /bin/zsh -l
  501 72565 69058   0 10:09PM ttys004    0:00.00 ./smsh1

> (Ctrl + D)=> 종료


*/