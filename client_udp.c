#include	<uma.h>

#include	<stdlib.h>
#include	<sys/socket.h>
#include	<sys/types.h>
#include	<netinet/in.h>

#include	<string.h>
#define SIZE 256
int main ( int c , char *v[] )
{
	int sock_c ;

	struct sockaddr_in client ;

	int length;

	char buffer[ SIZE ]  = "" ;

	length = sizeof ( client ) ;

	if ( c!=3 ) {

		printf("usage %s <ip address> <port number>\n", v[0]);
		
		exit ( EXIT_FAILURE );

	}

	if ( ( sock_c = socket ( AF_INET , SOCK_DGRAM , 0 ) ) == FAILED ) {
		
		perror ( "socket creation" ) ;
		
		exit ( EXIT_FAILURE ) ;

	}

	client . sin_family = AF_INET ;

	client . sin_port = htons ( atoi ( v[2] ) ) ;

	client . sin_addr . s_addr = inet_addr( v[1] ) ;// INADDR_ANY ;

	while ( 1 ) {
				bzero ( buffer , 255 ) ;

				puts("enter data");

				fgets(buffer , 255 , stdin);
	
			if ( ( sendto ( sock_c , buffer , SIZE , 0 , ( struct sockaddr*)&client , length) ) < 0 ) {

				perror("sending");

				exit ( EXIT_FAILURE );

				}
	
				bzero ( buffer , 255 ) ;

				puts("wait till other responds");

			if ( recvfrom ( sock_c ,buffer ,  255 , 0 , (struct sockaddr*) &client , &length ) < 0 ) {

				perror("sending");

                exit ( EXIT_FAILURE );

                }

				printf("the received message is %s \n" , buffer); 

			}
}
