/* 
file: myhello.c
author: 2018117610_moon jun yong
datetime: 2021-10-15 12:45
description:
	사용자로부터 메세지 입력 받은 후, Enter키를 치면, curse 화면에 메세지 출력
	타이머 시그널을 사용하여 0.25초(0.250ms)간격으로 애니메이션
	-sleep, usleep함수 사용하면 안됨
	compile cc myhello.c -lcurses -o myhello
*/
#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <sys/time.h>			/* for use setitimer */
#include <signal.h>
#include <stdlib.h>

#define LEFTEDGE	10
#define RIGHTEDGE	30
#define ROW		10
#define MESSAGE		10

/* Global variable */
char message[MESSAGE];
char blank[MESSAGE];

/* Functions */
int set_ticker(int n_msecs);
void animation(int signum);

/* Main */
int main()
{
	int i;
	int m_size;		/* sizeof message */
	
	/* inisialize of message, blank */
	for(i = 0; i < MESSAGE; i++) {
	 	message[i] = '\n';
		blank[i] = '\n';
	}
	
	/* input message */
	printf("메세지 입력 : ");
	fgets(message, sizeof(message), stdin);
	m_size = sizeof(message);
	
	/* blank_size */		
	for(i = 0; i < m_size; i++) {		
		blank[i] = ' ';
	}
	initscr();
	clear();
	/*타이머 시그널을 사용하여 0.25초 간격으로 애니메이션 */
	signal(SIGALRM, animation);
	if( set_ticker(250) == -1)
	    	perror("set_ticker");
	else
	    	while(1)
		    	pause();
	return 0;
}
int set_ticker(int n_msecs)
{
	struct itimerval new_timeset;
	long n_sec, n_usecs;
	
	n_sec = n_msecs / 1000;			/* int part 	*/
	n_usecs = (n_msecs % 1000) *1000L;	/* remainder 	*/
	
	new_timeset.it_interval.tv_sec = n_sec;		/* set reload	*/
	new_timeset.it_interval.tv_usec = n_usecs;	/* new ticker value */	
	new_timeset.it_value.tv_sec = n_sec;		/* store this	*/
	new_timeset.it_value.tv_usec = n_usecs;		/* and this	*/
	
	return setitimer(ITIMER_REAL, &new_timeset, NULL);     	
}
void animation(int signum)
{
    	int dir = +1;
	int pos = LEFTEDGE;
	
	while(1) {
		move(ROW, pos);
		addstr(message);
		move(LINES-1, COLS-1);
		refresh();

		move(ROW, pos);
		addstr(blank);
		pos += dir;

		if(pos >= RIGHTEDGE)
	    		dir = -1;
		if(pos <= LEFTEDGE)
	    		dir = +1;
	}
}




