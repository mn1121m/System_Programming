/* file: psh1.c - prompting sh11 version1 

description:    Prompts for the command and its arguments.
                Builds the argument vector for the call to execvp.
                Uses execvp(), and never returns.

*/

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXARGS 20
#define ARGLEN  100

char* makestring(char* );
int execute(char* []);

int main()
{

    return 0;
}

int execute(char *arglist[])
{

}
char* makestring(char buf)
{

}