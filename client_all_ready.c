#include	<uma.h>
#include	<stdlib.h>
#include	<string.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUF_SIZE 256
#define CLIENT_CONNECTIONS 5

int main ( int c , char * v[] ) 
{


		struct sockaddr_in server ;
		struct hostent *server_ent ;
		int sock_c ;
		int length  = sizeof ( server ) ;
		char buffer[ BUF_SIZE ] ="";

		if ( c != 3 ) {
				printf("usage : %s <ip address> <port number>\n",v[0]);
				exit ( EXIT_FAILURE );
		}
	
		length = sizeof ( server /* or client */) ;

		/* creating a socket */
	
		if ( ( sock_c = socket ( AF_INET , SOCK_STREAM , 0 ) ) == FAILED ) {

				perror("creation");

				exit ( EXIT_FAILURE ) ;

		}

		if ( ( server_ent = gethostbyname ( v[1] ) ) == NULL ) {

				perror("creation");

				exit ( EXIT_FAILURE ) ;

		}

		bzero ( ( char*) &server , sizeof( server ) ) ;

		server.sin_family = AF_INET ;

		bcopy ( (char*)server_ent -> h_addr , ((char*) &server .sin_addr.s_addr) , server_ent -> h_length ) ;

		server .sin_port = htons ( atoi ( v[2] ) ) ;
		
//		server .sin_addr.s_addr = inet_addr ( "0.0.0.0" );;

		if ( connect ( sock_c , (struct sockaddr*)&server , length ) < 0 ) {

				perror("connextion");

				exit ( EXIT_FAILURE ) ;

		}

		while (1) {

		puts("you might wanna enter something");

		bzero ( buffer , BUF_SIZE ) ;

		if ( fgets ( buffer , BUF_SIZE -1 ,stdin ) == NULL ) {

				perror("reading not");

				exit ( EXIT_FAILURE );

		}
		puts("wait till other responds:");
		
		bzero ( buffer , BUF_SIZE ) ;

		if (  ( write ( sock_c , buffer , strlen(buffer) ) ) < 0 ) {

				perror("reading not");

				exit ( EXIT_FAILURE );

		}
		bzero ( buffer , BUF_SIZE ) ;

		        if (  ( read ( sock_c , buffer , 255 ) ) < 0 ) {

                perror("reading not");

                exit ( EXIT_FAILURE );

        }

		printf("data is %s\n",buffer);
	}


}
