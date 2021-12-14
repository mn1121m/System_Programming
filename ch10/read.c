/* not complete
file:           read.c
author:     2018117610_moonjunyong
datetime:   2021.12.5
description:
            shows two more methods for redirecting standard input
            use #define to set one or the other
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
    FILE *fp = NULL;
    
    fp = fopen("data2.txt", "r"); /* open the disk file */

    /* redirect input   */
    fscanf(fp, "%s", line);
    #ifdef CLOSE_DUF
            close(0);
            newfd = dup(fd)             /* copy open fd to 0 */
    #else
            newfd = dup2(fp, 0);        /* close 0, dup fd to 0 */
    #endif
            if( newfd != 0) {
                fprintf(stderr, "Could not duplicate fd to 0\n");
                exit(1);
            }
            fclose(fp);
            printf("%s\n", line);
}
/* result
정상)
moonjunyong@munjun-yong-ui-MacBookPro ch10 % sort < data2.txt
0
1
2
3
4
5
6
7
8

--------------------------------------------------------
(비정상)
moonjunyong@munjun-yong-ui-MacBookPro ch10 % ./read sort data2.txt
Could not duplicate fd to 0
*/