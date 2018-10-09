#include    <netinet/in.h>
#include    <sys/socket.h>

#define BUF_MAX 256

void main ( int c , char * v[] )
{
    char buf [ BUF_MAX ] ;
    int activesocket ;
    struct sockaddr_in remoteaddr;
    struct sockaddr_in localaddr;
	struct hostent *hptr ;
    socklen_t remoteaddrlen;
	if ( c != 3 ) {
		printf("usage: %s <localhost> <port number>") ;
		exit (-1);
	}	

    activesocket = socket ( AF_INET , SOCK_DGRAM , 0 ) ;

    memset ( &remoteaddr , 0 , sizeof ( remoteaddr ) ) ;

    remoteaddr.sin_port = htons ( 80 ) ;
    hptr = gethostbyname ( v[1] );
    memcpy ( (char*)&remoteaddr.sin_addr.s_addr,hptr -> h_addr_list[0],hptr -> h_length);
    memset ( buf , 0 , BUF_MAX ) ;

    while ( gets(buf) ) {
	sendto (activesocket , buf , sizeof ( buf ) , 0 , &remoteaddr , sizeof ( remoteaddr ) ) ;
                    memset ( buf , 0 , sizeof ( buf ) ) ;
		    recvfrom ( activesocket , buf , BUF_MAX , 0 , &remoteaddr , &remoteaddrlen );
		    puts( buf );
            }
	close ( activesocket ) ;
    }
