/* mywho.c
2018117610_moonjunyong
2021-09-25 15:45

who3.c	- who with buffered reads
	- surpresses empty records
	- formats time nicely
	- buffers input (using utmplib)
 */

#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "utmp.h"
/* #define SHOWHOST */

#define INIT_PROCESS 5
#define LOGIN_PROCESS 6
#define USER_PROCESS 7
#define DEAD_PROCESS 8

// Data structure
struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

// Funtions
void show_info(struct utmp* );
void showtime(time_t);


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
    	time_t t = time(NULL);
	struct tm tm =  *localtime(&timeval);
	

    	printf("%d-%d-%d %d:%d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
}


