#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main ( void ) {

		struct sockaddr_in dest;

		char *ip;
		memset(&dest, '\0', sizeof(dest));
		dest.sin_addr.s_addr = inet_addr("216.58.220.46");
		printf ( "%u\n" , dest.sin_addr.s_addr ) ;
		perror("no idea");

		ip = inet_ntoa(dest.sin_addr);

		printf("IP Address is: %s\n",ip);


}

