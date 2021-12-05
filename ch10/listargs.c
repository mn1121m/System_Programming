/* listargs.c
    print the number of command line args, list the args, 
    then print a message to stderr
*/
#include <stdio.h>

int main(int ac, char *av[])
{
    int i;

    printf("Number of args: %d, Args are: \n", ac);

    for(i =0 ; i < ac; i++) {
        printf("args[%d] %s\n", i, av[i]);
    }
    fprintf(stderr, "This message is sent to stderr.\n");
}

/* compile

cc listargs.c -o listargs
./listargs testing one two
*/

/* result

Number of args: 4, Args are: 
args[0] ./listargs
args[1] testing
args[2] one
args[3] two
This message is sent to stderr.
*/

/* compile -> result

ch10 % ./listargs testing >xyz one two 2> oops
ch10 % cat xyz
Number of args: 4, Args are: 
args[0] ./listargs
args[1] testing
args[2] one
args[3] two

ch10 % cat oops 
This message is sent to stderr.
*/