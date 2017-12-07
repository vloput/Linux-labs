#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>

int main(void)
{
    int server_sockfd;
    int client_sockfd;
    int server_len;
    int client_len;
    
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;
    
    unlink("server_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    server_address.sun_family = AF_UNIX;
    
    strcpy(server_address.sun_path, "server_socket");
    server_len = sizeof(server_address);
    
    bind(server_sockfd, (struct sockaddr*) &server_address, server_len);
    listen(server_sockfd, 5);
    
    int message;
    int answer;
    
    client_len = sizeof(client_address);
    client_sockfd = accept(server_sockfd, (struct sockaddr*) &client_address, &client_len);
    
    while(1)
    {
        printf("server waiting...\n");

        read(client_sockfd, &answer, sizeof(int));
        printf("got from client %i\n", answer);

        message = answer * answer;

        write(client_sockfd, &message, sizeof(int));
        sleep(1);
    }
    
    close(client_sockfd);

    return 0;
}