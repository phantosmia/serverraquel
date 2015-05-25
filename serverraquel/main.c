//gcc -g daytimeserver.c -o server
#include <sys/socket.h>
#include <pthread.h>
#include <time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//referencing the textbook "Unix Network Programming"
//and the header file the book uses "unp.h"
#define LISTENQ 1024
#define MAXLINE 4096
#define BUFFSIZE 8192
#define	SA	struct sockaddr

int main(int argc, char **argv)
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    servaddr.sin_port = htons(1024);
    
    bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    
    listen(listenfd, LISTENQ);
    
    for(; ;)
    {
        connfd = accept(listenfd, (SA *) NULL, NULL);
        
        ticks = time(NULL);
        
        snprintf(buff, sizeof(buff), "%24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));
        
        close(connfd);
    }
}