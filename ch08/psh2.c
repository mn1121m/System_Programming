/* file: psh1.c - prompting sh11 version1 

description:    Solve the 'one-shot' problem of version1
                Uses execvp(), buf fork()s first so that the 
                shell waits around to perform another command
                New problem: shell catches signals. Run vi, press ^c

*/

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXARGS 20
#define ARGLEN  100

char* makestring(char* );
void execute(char* []);

int main()
{
    char *arglist[MAXARGS+1];   /* an array of pts */
    int numargs = 0;            /* index into array */
    char argbuf[ARGLEN];        /* read stuff here  */

    while (numargs < MAXARGS) {
        printf("Arg[%d]? ", numargs);
        if( fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n')
            arglist[numargs++] = makestring(argbuf);
        else {  // 입력 첫 문자가 '\n'할 때
            if( numargs > 0) {              // any args ?
                arglist[numargs] = NULL;    // clear list
                execute(arglist);           // do it
                numargs = 0;
            }
        }
    }
    return 0;
}

// use fork and execvp and wait to do it
void execute(char *arglist[])
{
    int pid, exitstatus;            /* of child */

    pid = fork();
    switch (pid) {
    case -1:
        perror("fork failed");
        exit(1);
    case 0:
        execvp(arglist[0], arglist);
        perror("execvp failed");
        exit(1);
    default:
        while(wait(&exitstatus) != pid);
            
        printf("child exited with status %d, %d\n", exitstatus>>8, exitstatus&0377);
    }
}
// trim off newline and create storage for the string
char* makestring(char *buf)
{
    char *cp;

    buf[strlen(buf)-1] = '\0';  /* trim newline */
    cp = malloc(strlen(buf)+1); /* get memory   */
    if( cp == NULL) {
        fprintf(stderr, "no memory\n");
        exit(1);
    }
    strcpy(cp, buf);
    return cp;
}