/*
AF_INET	IPv4 protocols
AF_INET6	IPv6 protocols
AF_LOCAL	Unix domain protocols
AF_ROUTE	Routing Sockets
AF_KEY	Ket socket 
*/

/*
SOCK_STREAM	Stream socket
SOCK_DGRAM	Datagram socket
SOCK_SEQPACKET	Sequenced packet socket
SOCK_RAW	Raw socket
*/

/*
IPPROTO_TCP	TCP transport protocol
IPPROTO_UDP	UDP transport protocol
IPPROTO_SCTP	SCTP transport protocol
*/


#include <sys/types.h>          

#include <sys/socket.h>

#include <stdlib.h>

#include <stdio.h>

int _connect(int sockfd, struct sockaddr *serv_addr, int addrlen);

int _socket(int domain, int type, int protocol);

int _bind(int sockfd, struct sockaddr *my_addr,int addrlen);

int _listen(int sockfd,int backlog);

//backlog − It is the number of allowed connections.

int _accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);

/*cliaddr − It is a pointer to struct sockaddr that contains client IP address and port.

addrlen − Set it to sizeof(struct sockaddr).*/

int _send(int sockfd, const void *msg, int len, int flags);


int _recv(int sockfd, void *buf, int len, unsigned int flags);

int _sendto(int sockfd, const void *msg, int len, unsigned int flags, const struct sockaddr *to, int tolen);

ssize_t _read(int fd, void *buf, size_t count);

int main ( void ) 
{
	int desc ;
	
	struct sockaddr serveraddr ;
	
	int serveraddrlen ;
	
	desc = socket( AF_INET, SOCK_DGRAM, 0 );
	
	printf("descriptor is %d\n" , desc);

	if ( connect(desc, &serveraddr, serveraddrlen) ) {
			perror("connection");
			exit ( EXIT_FAILURE );
	}
	
	
	close ( desc ) ;
}


