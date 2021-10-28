/*
play_again4.c
2018117610 moon jun yong
datetime: 2021-10-8 13:00 -> 2021-10-28(updated)
	purpose: ask if user vants another transaction
	method: set tty into char-by-char mode, no-echo mode
		set tty into no-delay mode
		read char, return result
		resets terminal modes on SIGINT, ignores SIGQUIT
	returns: 0=>yes, 1=>no, 2=>timeout
	better: timeout if user walks away
*/
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>	/* use for sleep()	*/
#include <ctype.h>	/* use for tolwer()	*/
#include <stdlib.h>	/* use for exit()	*/

#define ASK		"Do you want another transaction"
#define TRIES		3		/* max tries */
#define SLEEPTIME	2		/* time per try */
#define BEEP		putchar('\a')	/* alert user */

int get_response(char *question, int maxtries);
int get_ok_char();
void set_cr_noecho_mode();
void set_nodelay_mode();
void ctrl_c_handler(int signum);
void tty_mode(int how);

int main(void)
{
	int response;
	void ctrl_c_handler(int);

	tty_mode(0);				/* save current mode */
	set_cr_noecho_mode();			/* set -icanon, -echo */
	set_nodelay_mode();			/* noinput => EOF */
	signal(SIGINT, ctrl_c_handler);		/* handle INT	*/
	signal(SIGQUIT, SIG_IGN);		/* ignore QUIT signals */
	response = get_response(ASK, TRIES);	/* get some answer */
	tty_mode(1);				/* restore orig state */
	return response;
}

int get_response(char *question, int maxtries)
/*
	purpose:	ask a question and wait for a y/n answer or timeout
	method:		use getchar and complain about non-y/n input
	returns:	0=>yes, 1=>no
*/
{
    	int input;
	printf("%s (y/n)?", question);			/* ask		*/
	fflush(stdout);					/* force output */
	while(1) {
	    	sleep(SLEEPTIME);			/* wait a bit 	*/
		input = tolower(get_ok_char());		/* get next chr */
		 if( input == 'y')
		     	return 0;
		 if( input == 'n')
		     	return 1;
		 if( maxtries-- == 0)			/* outatime? 	*/
		     	return 2;			/* sayso	*/
		 BEEP;
	}
}

/*
*	skip over non-legal chars and return y, Y, n, N or EOF
*/
int get_ok_char()
{
    	int c;
	while( ( c = getchar() ) != EOF && strchr("yYnN", c) == NULL);
	
	return c;
}

void set_cr_noecho_mode(void)
/*
	purpose: put file descriptor 0 into chr-by-chr-mode and noecho mode
	method: use bite in termios
*/
{
    	struct termios ttystate;
	
	tcgetattr(0, &ttystate);		/* read curr. setting */
	ttystate.c_lflag	&= ~ICANON;	/* no buffering */
	ttystate.c_lflag	&= ~ECHO;	/* no echo either */
	ttystate.c_cc[VMIN]	= 1;		/*get 1 char at a time */ 
	tcsetattr(0, TCSANOW, &ttystate);	/* install settings */
}

void set_nodelay_mode()
/*
	purpose: put file descripter 0 into no-delay mode
	method: use fcntl to set bits
	notes:	tcsetattr() will do someting similar, but it is complicated
*/
{
    	int termflags;
	termflags = fcntl(0, F_GETFL);		/* read curr. settings */
	termflags |= O_NDELAY;			/* flip on nodelay bit */
	fcntl(0, F_SETFL, termflags);		/* and install 'em	*/
}

void ctrl_c_handler(int signum)
/*
	purpose: called if SIGINT is detected
	action: reset tty and scream
*/
{
    	tty_mode(1);
	exit(1);
}
/*	how == 0 => save current mode, how == 1 => restore mode */
/*	this version handles termios and fcntl flags		*/
void tty_mode(int how)
{
	static struct 	termios original_mode;
	static int		original_flags;
	if( how == 0) {
		tcgetattr(0, &original_mode);
		original_flags = fcntl(0, F_GETFL);
	}
	else {
	    	tcsetattr(0, TCSANOW, &original_mode);
		fcntl(0, F_SETFL, original_flags);
	}
}

