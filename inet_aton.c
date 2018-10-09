#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
int main ( void ) 
{
		int retval;
		struct in_addr addrptr;

		memset(&addrptr, '\0', sizeof(addrptr));
		retval = inet_aton("172.16.5.151", &addrptr);
		printf("ret val is %d\n", retval) ;
		printf( " %u\n",addrptr . s_addr) ;
}

