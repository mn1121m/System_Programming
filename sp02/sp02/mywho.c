/*
file: mywho.c
author: 2018117610_moonjunyong
datetime: 2021-10-22 (updated)
description:
who3.c	- who with buffered reads
	- surpresses empty records
	- formats time nicely
	- buffers input (using utmplib)
 */

#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include "utmp.h"
#include <unistd.h>	/* utmp_open, utmp_next, utmp_close */

#include <time.h>	/* edit showtime()-> localtime	*/
/* #define SHOWHOST */

#define INIT_PROCESS 5
#define LOGIN_PROCESS 6
#define USER_PROCESS 7
#define DEAD_PROCESS 8

// Funtions
void show_info(struct utmp* );
void showtime(time_t);

// Functions in <unistd.h> 
int utmp_open(char *filename);
struct utmp *utmp_next();
int utmp_reload();
void  utmp_close();

// Main
int main(void)
{
	struct utmp	*utbufp,	/* holds pointer to next rec */
    			*utmp_next();	/* returns pointer to next */
	if( utmp_open(UTMP_FILE) == -1) {
	    	perror(UTMP_FILE);
		exit(1);
	}
	while( (utbufp = utmp_next() ) != ( (struct utmp *) NULL) )
	    	show_info(utbufp);
	utmp_close();
	return 0;
}

void show_info(struct utmp* utbufp)
{
    if( utbufp->ut_type != USER_PROCESS)
	   return;

    printf("%-8.8s", utbufp->ut_name);
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);
    printf(" ");
    showtime( utbufp->ut_time );
#ifdef SHOWHOST
    	printf("(%s)", utbufp->ut_host);
#endif
	printf("\n");
}

void showtime( long timeval)
{
    time_t curTime = time(NULL);
    struct tm KST = *localtime(&curTime);	/* Korean Standard Time */
    printf("%d-%d-%d %d:%d\n", KST.tm_year +1900, KST.tm_mon +1, KST.tm_mday,
    KST.tm_hour, KST.tm_min);
    
}

