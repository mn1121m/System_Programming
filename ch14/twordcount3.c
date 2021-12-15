/*
twordcount3.c   -   threaded word counter for two files.
                -   Version 3: one counter per file.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

// Funtion
void *count_words(void *a);

// Data structure
struct arg_set {                /* two values in one arg    */
            char *fname;        /* file to examine  */
            int count;          /* number of words  */
};

// Main
int main(int ac, char *av[])
{
    pthread_t t1, t2;               /* two threads  */
    struct arg_set args1, args2;    /* two argsets  */

    if( ac != 3) {
        printf("usage: %s file1 file2\n", av[0]);
        exit(1);
    }
    args1.fname = av[1];
    args1.count = 0;
    pthread_create(&t1, NULL, count_words, (void *) &args1);

    args2.fname = av[2];
    args2.count = 0;
    pthread_create(&t1, NULL, count_words, (void *) &args2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("%5d: %s\n", args1.count, av[1]);
    printf("%5d: %s\n", args2.count, av[2]);
    printf("%5d: total words\n", args1.count+args2.count);
    
}
void *count_words(void *a)
{
    struct arg_set *args = a;
    FILE *fp;
    int c, prevc = '\0';

    if( (fp = fopen(args->fname, "r")) != NULL) {
        while( (c = getc(fp)) != EOF) {
            if( !isalnum(c) && isalnum(prevc) )
                    args->count++;
            prevc = c;
        }
        fclose(fp);
    } else
        perror(args->fname);
    return NULL;
}
/* compile & result
-----------------------------------
 cc twordcount3.c -lpthread -o twc3         //compile
 ----------------------------------
 ./twc3 text1 text2                         //compile
    7: text1
    5: text2
   12: total words
-----------------------------------

-----------------------------------
[Different result]
 wc -w /etc/group text1
     190 /etc/group
       7 text1
     197 total
-----------------------------------
*/