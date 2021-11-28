/* file: filedemo3.c 
-   show how the return value from fork()
    allows a process to determine whether
    it is a child or process
*/

#include <stdio.h>
#include <unistd.h>

int main()
{
    int fork_rv;
    printf("BeforeL my pid is %d\n", getpid());

    fork_rv = fork();               /* create new process */
    if( fork_rv == -1)              /* check error        */
        perror("fork"); 
    else if (fork_rv == 0)          /* if child is ok       */
        printf("I am the child. my pid = %d\n", getpid());
    else                            //parent
        printf("I am the parent. my child is %d\n", fork_rv);

}
