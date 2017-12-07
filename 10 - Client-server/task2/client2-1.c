#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>

int main(void)
{
    int sockfd;
    int len;
    int result;
    struct sockaddr_un address;
    
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *) &address, len);
    
    if(result == -1)
    {
        printf("error in connection\n");
    }
    
    int count = 0;
    int num = 0;

    while(count < 10)
    {
        count++;
        num += count;
    }

    write(sockfd, &num, sizeof(int));
    
    printf("Connection is over\n");
    
    close(sockfd);

    return 0;

}