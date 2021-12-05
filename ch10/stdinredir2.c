/* stdinredir2.c
author:     2018117610_moonjunyong
datetime:   2021.12.5
description:
            shows two more methods for redirecting standard input
            use #defien to set one or the other
*/
#include    <stdio.h>
#include    <unistd.h>
#include    <fcntl.h>
#include    <stdlib.h>
#define     CLOSE_DUP   /*  open, close, dup, close */
#define     USE_DUP2    /*  open, dup2, close   */

int main()
{
    int fd;
    int newfd;
    char line[100];

    /* read and print three lines   */
    fgets( line, 100, stdin ); printf("%s", line);
    fgets( line, 100, stdin ); printf("%s", line);
    fgets( line, 100, stdin ); printf("%s", line);

    /* redirect input   */
    fd = open("/etc/passwd", O_RDONLY); /* open the disk file */

    #ifdef CLOSE_DUF
            close(0);
            newfd = dup(fd)             /* copy open fd to 0 */
    #else
            newfd = dup2(fd, 0);        /* close 0, dup fd to 0 */
    #endif
            if( newfd != 0) {
                fprintf(stderr, "Could not duplicate fd to 0\n");
                exit(1);
            }
            close(fd);

            /* read and print three lines */
            fgets( line, 100, stdin); printf("%s", line);
            fgets( line, 100, stdin); printf("%s", line);
            fgets( line, 100, stdin); printf("%s", line);

}