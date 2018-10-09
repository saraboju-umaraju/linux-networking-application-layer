#include	<string.h>
#include	<uma.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#define MAX_CONNECTIONS 2
#define MAX_DATA 1024

int main ( int c , char *v[] )
{
		int sock_s ;
		int sock_c ;
		socklen_t length ;
		int sent ;
		int data_len ;
		char data [ MAX_DATA ] ="";
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

				printf("new client connected from %d port and ip is %s \n" , ntohs (client . sin_port) ,inet_ntoa( client . sin_addr )) ;
				data_len = 1 ;
				while ( data_len && data_len != FAILED) {
						data_len = recv (  sock_c , data , MAX_DATA , 0 ) ;
						if (data_len ) {
								send ( sock_c , data , data_len , 0 /*no idea for now*/) ;
								data[data_len] = 0 ;
								printf ("sent message is %s \n" , data );
						}
				}
				printf ("client disconnected\n");
				close ( sock_c ) ;

		}
}
