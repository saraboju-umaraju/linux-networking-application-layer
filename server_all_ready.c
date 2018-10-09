#include	<uma.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <arpa/inet.h>
#include <netinet/in.h>
#include <linux/libc-compat.h>

#define BUF_SIZE 256
#define CLIENT_CONNECTIONS 5

int main ( int c , char * v[] ) 
{


		struct sockaddr_in server ;
		struct sockaddr_in client ;
		int sock_s ;
		int sock_c ;
		int length ;
		char buffer[ BUF_SIZE ] ="";

		if ( c != 2 ) {
				printf("usage : %s <port number>\n",v[0]);
				exit ( EXIT_FAILURE );
		}

		length = sizeof ( /*server*/struct sockaddr_in /* or client */) ;

		/* step 1: creating a socket */

		if ( (sock_s = socket ( AF_INET , SOCK_STREAM , 0 ) ) == FAILED ) {

				perror ("socket creation");

				exit ( EXIT_FAILURE ) ;
		}


		/* lets fill our details to bind */

		server . sin_family = AF_INET ;

		server . sin_port = htons ( 0 ) ;

		server . sin_addr . s_addr = INADDR_ANY ;

		bzero ( &server . sin_zero , 8 ) ;

//		int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
			getsockname( sock_s , &server , &length ) ;

			perror("");

		printf("%s\n" , inet_ntoa ( server . sin_addr ) );
		
		printf("%d\n" , ntohs ( server . sin_port) );
		
		printf("%d\n" , ntohs ( server . sin_family) );


		if ( listen ( sock_s , CLIENT_CONNECTIONS-3 ) == FAILED ) {
				perror("unusual error");

				exit( EXIT_FAILURE ) ;
		}
		puts("second");
			getsockname( sock_s , &server , &length ) ;

			perror("");

		printf("%s\n" , inet_ntoa ( server . sin_addr ) );
		
		printf("%d\n" , ntohs ( server . sin_port) );
		
		printf("%d\n" , ntohs ( server . sin_family) );

		/* step 2 : binding a socket */

		if (  ( bind ( sock_s , ( struct sockaddr* ) &server , length ) )== FAILED ) {

				perror("binding socket");

				exit ( EXIT_FAILURE ) ;
		}
			getsockname( sock_s , &server , &length ) ;

			perror("");

		printf("%s\n" , inet_ntoa ( server . sin_addr ) );
		
		printf("%d\n" , ntohs ( server . sin_port) );
		
		printf("%d\n" , ntohs ( server . sin_family) );


		/* step 3 : start listening for clients */

		if ( listen ( sock_s , CLIENT_CONNECTIONS ) == FAILED ) {

				perror("unusual error");

				exit( EXIT_FAILURE ) ;
		}
		puts("fst");
		/*step 4 : accept client requests */

		if ( ( sock_c = accept ( sock_s , ( struct sockaddr* ) &client , &length ) ) == FAILED ){

				perror("accept ");

				exit ( EXIT_FAILURE ) ;

		}



		/* step 5 : process whatever you wish */

		//printf("client ip address : %s\n", (char*)inet_ntoa(client.sin_addr.s_addr));

		while (1)
		{
				bzero ( buffer , BUF_SIZE ) ;

				puts("wait till client respond");
				
				//printf ("message from ip : %s  port %d is :%s \n", (char*)inet_ntoa( client . sin_addr . s_addr ) , ntohs( client . sin_port ),buffer) ;
		
				if ( read ( sock_c , buffer , BUF_SIZE ) < 0 ) {

						perror("read"); 

						exit ( EXIT_FAILURE );
				}

				buffer [ strlen(buffer) - 1] = '\0' ;

				printf ("message from ip : %s  port %d is :%s \n", (char*)inet_ntoa( client . sin_addr . s_addr ) , ntohs( client . sin_port ),buffer) ;

				printf("enter your message to %s :",(char*)inet_ntoa( client . sin_addr . s_addr )) ;
				
				bzero ( buffer , BUF_SIZE ) ;
			
				fgets(buffer , BUF_SIZE , stdin);
			
				if ( write ( sock_c , buffer , BUF_SIZE ) < 0 ) {

						perror("read");

						exit ( EXIT_FAILURE );
				}
		}
		close ( sock_c ) ;
}

