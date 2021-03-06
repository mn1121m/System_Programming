/* whotofile.c
author: 20191187610_mmonjunyong
    purpose:    show how to redirect output for another program
    idea:       fork, then in the child, redirect ouput, then exec
*/

#include <stdio.h>
#include <unistd.h> /* for execlp   */
#include <stdlib.h> /* for exit     */
#include <fcntl.h>  /* use for creat() */

int main()
{
    int pid;
    int fd;

    printf("About to run who into a file\n");

    /* create a new process or quit */
    if( (pid = fork() ) == -1 ) {
        perror("fork"); exit(1);
    }
    /* child does the work */
    if ( pid == 0) {
        close(1);                       /* close */
        fd = creat( "userlist", 0644);  /* then open */
        execlp("who", "who", NULL);     /* and run  */
        perror("execlp");
        exit(1);
    }

    /* parent waits then report */
    if ( pid != 0) {
        wait(NULL);
        printf("Done running who. results in userlist\n");
    }
    return 0;
}
/* compile
$cc whotofile.c -o whotofile
$./whotofile

=> result
About to run who into a file
Done running who. results in userlist
--------------------------------------
$ cat userlist
moonjunyong console  Dec  2 15:14
*/