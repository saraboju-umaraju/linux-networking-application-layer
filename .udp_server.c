#include    <netinet/in.h>
#include    <sys/socket.h>

#define BUF_MAX 256

void main ( void )
{
    char buf [ BUF_MAX ] ;
    int passivesocket ;
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    socklen_t clientaddrlen;

    passivesocket = socket ( AF_INET , SOCK_DGRAM , 0 ) ;

    memset ( &serveraddr , 0 , sizeof ( serveraddr ) ) ;

    serveraddr.sin_family = AF_INET ;
    serveraddr.sin_port = htons ( 10000 ) ;
    serveraddr.sin_addr.s_addr = htonl ( INADDR_ANY ) ;

    bind ( passivesocket , (struct sockaddr *)&serveraddr , sizeof ( serveraddr ) ) ;
    clientaddrlen = sizeof ( serveraddr ) ;

    memset ( buf , 0 , BUF_MAX ) ;

    while ( BUF_MAX ) {
            while ( recvfrom ( passivesocket , buf ,BUF_MAX , 0 ,(struct sockaddr *) &clientaddr , &clientaddrlen ) > 0 ) {
                    sendto(passivesocket , buf , BUF_MAX , 0 , (struct sockaddr *)&clientaddr ,  clientaddrlen ) ;
                    memset ( buf , 0 , BUF_MAX ) ;
            }
    }

}

