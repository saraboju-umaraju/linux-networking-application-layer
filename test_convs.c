#include	<uma.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main ( char c , char *v[] ) 
{
	int ip = in_aton ( v[1] ) ;

	printf ( "%u\n" , ip ) ;

	return 0 ;

}

int in_aton(char *str) {
    unsigned long l;
    unsigned int val;
    int i;

    l = 0;
    for (i = 0; i < 4 ; i++) {
        l <<= 8;
        if (*str != '\0') {
            val = 0;
            while (*str != '\0' && *str != '.') {
                val *= 10;
                val += *str - '0';
                str++;
            }
            l |= val;
            if (*str != '\0')
                str++;
        }
    }
   return(htonl(l));
    return((l));
}

