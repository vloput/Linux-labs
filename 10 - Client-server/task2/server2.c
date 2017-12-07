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
    
    while(1)
    {
        printf("server waiting...\n");
        listen(server_sockfd, 5);
    
    	int answer;
    
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr*) &client_address, &client_len);

        read(client_sockfd, &answer, sizeof(int));
        
        if(answer < 100)
        {
            printf("Client 1 here\n");
        }
        else
        {
            printf("Client 2 here\n");
        }
    }
    
    close(client_sockfd);

    return 0;
}