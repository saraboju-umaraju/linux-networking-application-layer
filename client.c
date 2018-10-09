#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include    <stdlib.h>
#include    <string.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main (int argc , char **argv )
{

	int nfd;
	
	char *buff = (char *) malloc (200 * sizeof(char));

	struct sockaddr_in v1;
	socklen_t addrlen = sizeof( v1);
struct hostent *server_ent ;


	
if ( ( server_ent = gethostbyname ( argv[2] ) ) == NULL ) {

                perror("creation");

                exit ( EXIT_FAILURE ) ;

        }

        bzero ( ( char*) &v1 , sizeof( v1 ) ) ;

		printf("%s\n" ,  (char*)server_ent -> h_addr);;

        bcopy ( (char*)server_ent -> h_addr , ((char*) &v1 .sin_addr.s_addr) , server_ent -> h_length ) ;

/*	if ( (fd = bind(fd,( struct sockaddr * ) &v1, addrlen ) ) == -1 ) {
		perror("bind open");
		exit(0);
	}

	if ( (listen (fd, 5))  == -1 ) {
		perror("listen open");
		exit(0);
	}
	*/
     v1 . sin_family  = AF_INET;
     v1 . sin_port  = htons(atoi(argv[1]));
				
	if ( ( nfd = socket (AF_INET, SOCK_STREAM, 0) ) == -1 ) {
		perror("socket open");
		exit(0);
	}
	

	if ( ( connect (nfd, (struct sockaddr *) &v1 ,addrlen ) ) == -1 ) {
		perror("accept open");
		exit(0);
	}
	
		fgets(buff, 200, stdin);	
	
	if ((write(nfd,buff,strlen(buff) + 2 )) == -1 ) {
		perror("read open");
		exit(0);
	}
	
	return 0;
} 
	
