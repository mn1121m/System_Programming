/* timeclnt.c - a client for timeserv.c
*               usage: timeclnt hostname portnumber
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>

#define     oops(msg)   { perror(msg); exit(1); }

int main(int ac, char *av[])
{
    struct  sockaddr_in  servadd;   /*  the number to call      */
    struct  hostent     *hp;        /*  used to get number      */
    int     sock_id, sock_fd;       /*  the socket and fd       */
    char    message[BUFSIZ];        /*  to receive meassage     */
    int     messlen;               /*  for message length      */

    /*
    *   Step1: get a socket
    */
    sock_id = socket(PF_INET, SOCK_STREAM, 0);   /* get a socket, 0: TCP / 1: UDP    */
    if( sock_id == -1)
        oops("socket");
    
    /*
    *   Step2: connect to server
    */
    bzero( &servadd, sizeof(servadd) );     /* zero the address     */
    hp = gethostbyname( av[1]);             /* lookup host's ip#    */
    if( hp == NULL)
        oops(av[1]);
    bcopy(hp->h_addr, (struct sockaddr *)&servadd.sin_addr, hp->h_length);
    servadd.sin_port = htons(atoi(av[2]));    /* fill in port number  */
    servadd.sin_family = AF_INET;             /* fill in socket type  */

    if( connect(sock_id, (struct sockaddr*)&servadd, sizeof(servadd)) != 0)
        oops("bind");
    
    /*
    *   Step3: transfer data from server, than hangup     
    */
    messlen = read(sock_id, message, BUFSIZ);       /* read stuff   */
    if( messlen == -1)
        oops("read");
    if( write(1, message, messlen) != messlen)     /* adn write to */
        oops("write");
    close(sock_id);
}