/*
play_again2.c
2018117610 moon jun yong
datetime: 2021-10-8 12:00 -> 2021-10-28(updated)
	purpose: ask if user vants another transaction
	method: set tty into char-by-char mode, read char, return result
	returns: 0=>yes, 1=>no
	better: timeout if user walks away
*/
#include <stdio.h>
#include <termios.h>

#define QUESTION	"Do you want another transaction"

int get_response(char *);
void set_cr_noecho_mode(void);
void tty_mode(int);

int main(void)
{
	int response;

	tty_mode(0);				/* save mode */
	set_cr_noecho_mode();			/* set -icanon, -echo */
	response = get_response(QUESTION);	/* get some answer */
	tty_mode(1);				/* restore tty state */
	return response;
}

int get_response(char *question)
/*
	purpose:	ask a question and wait for a y/n answer
	method:		use getchar and ignore non y/n answers
	returns:	0=>yes, 1=>no
*/
{
    	int input;
	printf("%s (y/n)?", question);
	while(1) {
		switch(input = getchar() ) {
		    case 'y':
		    case 'Y': return 0;
		    case 'n':
		    case 'N':
		    case EOF: return 1;
		}
	}
}

void set_cr_noecho_mode(void)
/*
	purpose: put file descriptor 0 (i.e. stdin) into chr-by-chr-mode
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

/*	how == 0 => save current mode, how == 1 => restore mode */
void tty_mode(int how)
{
	static struct termios original_mode;
	if( how == 0)
		tcgetattr(0, &original_mode);
	else
	    	tcsetattr(0, TCSANOW, &original_mode);
}

