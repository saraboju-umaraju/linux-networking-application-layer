#include	<string.h>
#include	<uma.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#define MAX_CONNECTIONS 5

int main ( int c , char *v[] )
{
	int sock_s ;
	int sock_c ;
	socklen_t length ;
	int sent ;
	char message[] = "hello world in socketing\n" ;
	struct sockaddr_in server ;
	struct sockaddr_in client ;
	if ( c !=2 ) {
		printf("usage : %s <port number>\n" , v[0]) ;
		exit ( EXIT_FAILURE ) ;
	}

	length = sizeof ( struct sockaddr_in ) ;
	
	if (  ( sock_s = socket ( AF_INET , SOCK_STREAM , 0 ) ) == FAILED ) {
			perror ( "socket creation:" ) ;
			exit ( EXIT_FAILURE ) ;
	}
	
	server.sin_family = AF_INET ;
	server.sin_port = htons ( atoi( v[1] ) ) ;
	server.sin_addr.s_addr = INADDR_ANY  ;
	bzero ( &server.sin_zero , 8 ) ;
	
	if (  ( bind ( sock_s , ( struct sockaddr* ) &server , length ) ) == FAILED ) {
			perror ("socket binding:") ;
			exit ( EXIT_FAILURE ) ;
	}
	
	while ( 1 ) {
	
	if ( ( listen ( sock_s , MAX_CONNECTIONS ) ) == FAILED ) {
		perror ("waiting for client:") ;
		exit ( EXIT_FAILURE ) ;
	}
	puts("listening to clients "); 
	
	while ( 1 ) {

			if  ( ( sock_c = accept ( sock_s , (struct sockaddr *) &client , &length ) ) == FAILED ) {
					perror ("waiting for client:") ;
					exit ( EXIT_FAILURE ) ;
			}
			sent = send ( sock_c , message , strlen ( message ) , 0 /*no idea for now*/) ;

			printf ("sent %d bytes to client : %s \n" , sent , inet_ntoa ( client.sin_addr ) );
			
			close ( sock_c ) ;

	}
}

}
