#include    <uma.h>
#include    <stdlib.h>
#include    <string.h>
#include    <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <arpa/inet.h>
#include <netinet/in.h>
#include <linux/libc-compat.h>

#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/*     int select(int nfds, fd_set *readfds, fd_set *writefds,
	   fd_set *exceptfds, struct timeval *timeout);

	   void FD_CLR(int fd, fd_set *set);
	   int  FD_ISSET(int fd, fd_set *set);
	   void FD_SET(int fd, fd_set *set);
	   void FD_ZERO(fd_set *set); */

int main ( char c , char* v[] ) 
{
		struct sockaddr_in client ;

		int cfd = 0 ;

		int len = 0 ;

		char buff[100] = {} ;

		fd_set inst ;

		len = sizeof ( client ) ;

		if ( c != 3 ) {

				printf("usage: < %s > < ip address > < port num >\n" , v[0]);

				exit ( EXIT_FAILURE ) ;

		}

		if ( ( cfd = socket ( AF_INET , SOCK_STREAM , 0 ) ) < 0 ) {

				perror("socket creation");

				exit ( EXIT_FAILURE ) ;

		}

		client . sin_family = AF_INET ;

		client . sin_port = htons ( atoi ( v[2] ) ) ;

		client . sin_addr . s_addr = inet_addr ( v[1] ) ;

		if ( ( connect ( cfd , (struct sockaddr*) &client , len ) ) < 0 ) {

				perror("connetc");

				exit ( EXIT_FAILURE ) ;

		}

		while (1) {

				FD_ZERO ( &inst ) ;

				FD_SET ( 0 , &inst ) ; /* read fds */

				FD_SET ( cfd , &inst ) ; /* read fds */

				if ( select ( /* max fd + 1 */ cfd + 1 , /* inst */ &inst , NULL , NULL , NULL /* time till wait */ ) < 0 );

				if ( FD_ISSET ( 0 , &inst ) ) {

						fgets ( buff , 99 , stdin ) ;

						send ( cfd , buff , strlen(buff) + 1 , MSG_WAITFORONE ) ;

				}  

				if ( FD_ISSET ( cfd , &inst ) ) {

						memset ( buff , 0 , 99 ) ;

						recv ( cfd , buff , 99 , 0 ) ;

						puts(buff) ;

				}

		}

}




