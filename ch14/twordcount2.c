/*
twordcount2.c   -   threaded word counter for two files.
                -   Version2: users mutex to lock counter
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

// Global variable
int total_words;    
pthread_mutex_t counter_lock = PTHREAD_MUTEX_INITIALIZER;

// Function
void *count_words(void *f);     /* the counter and its lock */

// Main
int main(int ac, char *av[])
{
    pthread_t t1, t2;   /* two threads  */
    void    *count_words(void *);

    if( ac != 3) {
        printf("usage: %s file1 file2\n", av[0]);
        exit(1);
    }
    total_words = 0;
    pthread_create(&t1, NULL, count_words, (void*) av[1]);
    pthread_create(&t2, NULL, count_words, (void*) av[2]);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("%5d: total word\n", total_words);

    
}
void *count_words(void *f)
{
    char *filename = (char *)f;
    FILE *fp;
    int c, prevc = '\0';
    if( (fp = fopen(filename, "r")) != NULL) {
        while( (c = getc(fp)) != EOF) {
            if( !isalnum(c) && isalnum(prevc) ) {
                pthread_mutex_lock(&counter_lock);
                total_words++;
                pthread_mutex_unlock(&counter_lock);

            }
            prevc = c;
        }
        fclose(fp);
    } else
        perror(filename);
    return NULL;
}
/* compile & result
-----------------------------------
 cc twordcount2.c -lpthread -o twc2         //compile
 ----------------------------------
 ./twc2 text1 text2                         //compile
   12: total word                           //result
-----------------------------------
 ./twc2 /etc/group text1
  412: total word
-----------------------------------
 ./twc2 /etc/group text2
  410: total word
-----------------------------------
[Different result]
 wc -w /etc/group text1
     190 /etc/group
       7 text1
     197 total
-----------------------------------

*/