#include	<uma.h>

#include	<stdlib.h>

#include	<string.h>

#include    <sys/socket.h>

#include    <sys/types.h>

#include    <netinet/in.h>

#define SIZE 256

int main ( int c , char *v[] )
{
		int sock_c ;

		struct sockaddr_in server ;

		int length;

		char buffer[ SIZE ]  = "" ;

		length = sizeof ( server ) ;

		if ( c!=2) {

				printf("usage: %s <port number>",v[0]);

				exit ( EXIT_FAILURE);

		}

		if ( ( sock_c = socket ( AF_INET , SOCK_DGRAM , 0 ) ) == FAILED ) {

				perror ( "socket creation" ) ;

				exit ( EXIT_FAILURE ) ;

		}

		server . sin_family = AF_INET ;

		server . sin_port = htons ( atoi ( v[1] ) ) ;

		server . sin_addr . s_addr = (INADDR_ANY) ;

		if ( ( bind ( sock_c , ( struct sockaddr*) &server , length ) ) ) {

				perror("binding");

				exit ( EXIT_FAILURE ) ;

		}


		while ( 1 ) {
				
				bzero ( buffer , 255 ) ;

				puts("waiting on data");

				if ( ( recvfrom ( sock_c , buffer , SIZE , 0 , ( struct sockaddr*)&server , &length) ) < 0 ) {

						perror("receiving");

						exit ( EXIT_FAILURE );

				}

				printf("the received message is %s \n" , buffer); 
				
				bzero ( buffer , SIZE ) ;

				puts("enter data");

				fgets(buffer , SIZE , stdin);

				if ( ( sendto ( sock_c , buffer , SIZE , 0 , ( struct sockaddr*)&server , length) ) < 0 ) {

						perror("sending");

						exit ( EXIT_FAILURE );

				}


		}

}
