/*
file:	process.c - command processing layer
author:	2018117610_moonjunyong
datetime: 2021-11-19 23:30
description: 

The process(char **arglist) function is called by te main loop
It site in front of the execute() function. This layer handles
two main calsses of processing:
	a) built-in functions (e.g. exit(), set, =, read, ..)
	b) control structures (e.g. if, while, for)

*/
#include <stdio.h>
#include "smsh.h"

int is_control_command(char *);
int do_control_command(char **);
int ok_to_execute();

int process(char **args)
{
	int	rv = 0;
	if( args[0] == NULL)
	    	rv = 0;
	else if( is_control_command(args[0]) )
	    	rv = do_control_command(args);
	else if( ok_to_execute() )
	    	rv = execute(args);
	return rv;
}



