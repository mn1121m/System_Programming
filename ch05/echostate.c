/* 
file: echostate.c - chow state of echo bit
description:
		reports current state echo bit in tty driver for fd 0
		show how to read attributes from driver and test a bit
*/
#include	<stdio.h>
#include	<termios.h>
#include	<stdlib.h>

/* Main */
int main()
{
	struct	termios	info;
	int	rv;

	rv = tcgetattr(0, &info);	/* read values from driver */

	if( rv == -1) {
	    perror("tcgetattr");
	    exit(1);
	}
	if ( info.c_lflag & ECHO)	/* test a bit	*/
	    	printf("echo is on, since its bit is 1\n");
	else
	    	printf("echo is OFF, since its bit is 0\n");
}

