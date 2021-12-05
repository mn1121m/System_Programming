/* stdinredir1.c
author:     2018117610_moonjunyong
datetime:   2021.12.5
description:
            purpose:    show how to redirect standard input by replacing file
                        descriptor 0 with a connection to a file.
            action:     reads three lines from standard input, then
                        closes fd 0, opens a disk file, then read in
                        three more lines from standard input
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    int     fd;
    char    line[100];

    /* read and print three lines */

    fgets(line, 100, stdin); printf("%s", line);
    fgets(line, 100, stdin); printf("%s", line); 
    fgets(line, 100, stdin); printf("%s", line);

    /* redirect input */

    close(0);
    fd = open("/etc/passwd", O_RDONLY);
    if ( fd != 0) {
        fprintf(stderr, "Could not open data as fd 0\n");
        exit(1);
    }

    /* read and print three lines */
    fgets(line, 100, stdin); printf("%s", line);
    fgets(line, 100, stdin); printf("%s", line);
    fgets(line, 100, stdin); printf("%s", line);
}   

/* compile -> result
cc stdinredir1.c -o stdinredir1
./stdinredir1
line1
line1
testing line2
testing line2
line 3 here
line 3 here
##
# User Database
# 
----------------
cf) head -3 /etc/passwd     -> 맨위에서 밑으로 3줄만 보여준다
##
# User Database
# 