/* file: forkdemo1.c
-   show how fork creates two processes, distinguishable
    by the different return values from fork()
*/

#include <stdio.h>
#include <unistd.h>

int main()
{
    int ret_from_fork, mypid;

    mypid = getpid();
    printf("Before: my pid is %d\n", mypid);

    ret_from_fork = fork();

    sleep(1);
    printf("After: my pid is %d, fork() said %d\n",
    getpid(), ret_from_fork);
    
}
/* result
Before: my pid is 32161
After: my pid is 32161, fork() said 32162
After: my pid is 32162, fork() said 0

32161:  parent process id (original)
32162:  child process id (new)
0:      fork에 대한 결과값  
*/