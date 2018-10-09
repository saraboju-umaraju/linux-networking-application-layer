#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SIZE 30
int main(void)
{
	int sfd;
	
	char buf[SIZE];

	char buf2[SIZE];

	struct sockaddr_in ser;

	int addr_len;

	int data_size;

	
	sfd = socket(AF_INET ,SOCK_DGRAM,0);
	
	
	ser.sin_family = AF_INET ; 
	ser.sin_port = htons(2000);
	ser.sin_addr.s_addr = inet_addr("");

	addr_len = sizeof(struct sockaddr_in);

	while(1) {

		printf("enter message:  \n");
		fgets(buf , 255 , stdin);

		//send messaga to server
		sendto(sfd ,buf ,SIZE ,0,(struct sockaddr *)&ser ,addr_len);
		puts("wait till server respond:");
		//receive messaga from server
		data_size = recvfrom(sfd ,buf2 ,SIZE ,0 ,(struct sockaddr *)&ser ,&addr_len );
		printf("data from server %s\n",buf2);
	}
	return 0;
}


