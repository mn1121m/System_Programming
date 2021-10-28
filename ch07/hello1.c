/* hello1.c
	purpose show the minimal curses needed to use curses
	outline initialize, draw stuff, wait for input, quit
*/

#include <stdio.h>
#include <curses.h>

int main()
{
	initscr();	/* turn on curses 	*/

	clear();	/* send requests	*/
	move(10,20);		/* clear screen	*/
	addstr("Hello, world");	/* row 10, col 20 */
	move(LINES-1, 0);	/* move to LL	*/

	refresh();	/* update the screen	*/
	getch();	/* wait for user input	*/

	endwin();	/* turn off curses	*/
}
