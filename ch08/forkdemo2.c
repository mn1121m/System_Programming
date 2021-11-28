/* file: forkdemo2.c
-   show how child processes pick up at the return
    from fork() and can execute any code they like,
    even fork(). Predict number of lines of output.
*/

#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("my pid is %d\n", getpid() );
    fork();
    fork();
    fork();
    printf("my pid is %d\n", getpid() );
}
/* result parent: 1 / child: 8
my pid is 18950         // parent
my pid is 18950
my pid is 18953
my pid is 18952
my pid is 18951
my pid is 18955                                                                    
my pid is 18956
my pid is 18954
my pid is 18957
*/