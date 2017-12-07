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
    int count = 0;
    int num = 2;
    int answer;
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

    while(count++ < 4)
    {
        write(sockfd, &num, sizeof(int));
        sleep(1);
        read(sockfd, &answer, sizeof(int));
        printf("Number from server = %i\n", answer);
        num = answer;
    }
    
    printf("Connection is over");
    
    close(sockfd);

    return 0;
}