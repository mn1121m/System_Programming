//
// file: waitdemo3.c
// author: 2018117610_moonjunyong
// datetime: 2021-11-12 11:00
/* description : show how parent gets child status
		1) SIGCHID - 자식 프로세스가 종료될 때 부모 프로세스에 통보되는 POSIX신호 
		2) 1초간격으로 메세지 출력('parent is busy')
		3)'SIGCHLD' signal handler추가
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define DELAY 5

static void child_handler(int sig);

int main()
{
	int newpid;
	void child_code(), parent_code();

	printf("before: mypid is %d\n", getpid());
	if( (newpid = fork()) == -1)
		perror("fork");
	else if (newpid == 0)
		child_code(DELAY);
	else
		parent_code(newpid);	
}

/*
*	new process takes a nap and then exits
*/

void child_code(int delay)
{
	printf("child %d here. will sleep for %d seconds\n", getpid(), delay);
	sleep(delay);
	printf("child done, about to exit\n");
	exit(17);
}

/*
*	patent waits for child then prints a message
*/

void parent_code(int childpid)
{
	signal(SIGCHLD, (void*)child_handler);
	while(1) {
		printf("parent is busy ...\n");
		sleep(1);

	}
}

static void child_handler(int sig)
{
    int wait_rv;
	int child_status;
	int high_8, low_7, bit_7;
	
	wait_rv = wait(&child_status);
	
	high_8 = child_status >> 8;
	low_7 = child_status & 0x7F;
	bit_7 = child_status & 0x80;

	printf("status: exit = %d, sig = %d, core = %d\n", high_8, low_7, bit_7);
	exit(1);	//종료
}

