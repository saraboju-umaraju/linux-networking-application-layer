// UDP server program
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define SIZE 30
int main(void)
{
    //declarations
    int sfd;
    char buf[SIZE];
    char buf2[SIZE];
    struct sockaddr_in ser;
    int data_size;
    int addr_len;
    sfd = socket(AF_INET ,SOCK_DGRAM,0);

    if(sfd<0) {
        perror("socket");
    }

    ser.sin_family = AF_INET ;
    ser.sin_port = htons(2000);
    ser.sin_addr.s_addr = inet_addr("0.0.0.0");

    if(bind(sfd ,(struct sockaddr *)&ser ,sizeof(struct sockaddr_in))<0)
    {
        perror("bind");
    }

    addr_len = sizeof(struct sockaddr_in);

    while(1) {

		puts("wait till other person respond");
        
		data_size = recvfrom(sfd ,buf ,SIZE,0 ,(struct sockaddr *)&ser ,&addr_len );

        if(data_size < 0) {
            perror("recv from");
         }

        printf("sender:%s  \nenter your message:  ",buf);

        fgets(buf2 , 255 , stdin);


        sendto(sfd ,buf2 ,SIZE ,0 ,(struct sockaddr *)&ser ,addr_len );
    }
    return 0;
}


