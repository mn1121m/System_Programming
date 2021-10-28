/*
file : set_ticker.c
author: 2018117610_moon jun yong
datetime: 2021-10-15-12:10 -> 2021-10-28(updated)
description:
	arranges for interval timer to issues SIGLRM's at intervals
	returns -1 on error, 0 for OK
	arg in milliseconds, converted into whole seconds and microseconds
	note: set_ticker(0) turn off ticker
*/

#include <stdio.h>
#include <sys/time.h>

int set_ticker(int n_msecs)	// milliseconds
{
	struct itimerval new_timeset;
	long 	n_sec, n_usecs;

	n_sec = n_msecs / 1000;				/* int part	 */
	n_usecs = ( n_msecs % 1000) * 1000L;		/* remainder	 */

	new_timeset.it_interval.tv_sec = n_sec;		/* set reload	*/
	new_timeset.it_interval.tv_usec = n_usecs; 	/* new ticker value */
	new_timeset.it_value.tv_sec 	= n_sec;	/* store this		*/
	new_timeset.it_value.tv_usec	= n_usecs;	/* and this		*/

	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}



