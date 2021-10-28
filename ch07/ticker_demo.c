/*
file: ticker_demo.c
author: 2018117610 moon jun yong
datetime: 2021-10-15 12:00
description:	demonstrates use of interval timer to generate regular
		signals, which are in turn caught and used to count down
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>	/* setticker()		*/
#include <signal.h>
#include <stdlib.h>


int main()
{
	void countdown(int);
	signal(SIGALRM, countdown);
	if( set_ticker(500) == -1)
	    	perror("set_ticker");
	else
		while(1)
		    	pause();
	return 0;
}

void countdown(int signum)
{
	static int num =10;
	printf("%d ..", num--);
	fflush(stdout);
	if (num < 0) {
	    printf("DONE!\n");
	    exit(0);
	}
}


