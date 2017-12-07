#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>

int main(void)
{

    pid_t pid = fork();

    if (pid == -1)
    {
        printf("Error while creating new thread\n");
        return 0;
    }
    else if(pid == 0)   //Child thread
    {
        int server_sockfd_2;
        int client_sockfd_2;
        int server_len_2;
        int client_len_2;
        
        unlink("server_socket_2");
        struct sockaddr_un server_address_2;
        struct sockaddr_un client_address_2;

        server_sockfd_2 = socket(AF_UNIX, SOCK_STREAM, 0);
        server_address_2.sun_family = AF_UNIX;
        
        strcpy(server_address_2.sun_path, "server_socket_2");
        server_len_2 = sizeof(server_address_2);
        
        bind(server_sockfd_2, (struct sockaddr*) &server_address_2, server_len_2);
        
        while(1)
        {
            printf("Server 2 is waiting...\n");
            listen(server_sockfd_2, 5);     //Socket 2 listening
        
        	int answer;
        
            //Socket 2
            client_len_2 = sizeof(client_address_2);
            client_sockfd_2 = accept(server_sockfd_2, (struct sockaddr*) &client_address_2, &client_len_2);

            read(client_sockfd_2, &answer, sizeof(int));
            
            printf("We've got %i from client\n", answer);
        }
        
        close(client_sockfd_2);
    }
    else                //Parent thread
    {
        int server_sockfd_1;
        int client_sockfd_1;
        int server_len_1;
        int client_len_1;
        
        unlink("server_socket_1");
        struct sockaddr_un server_address_1;
        struct sockaddr_un client_address_1;

        server_sockfd_1 = socket(AF_UNIX, SOCK_STREAM, 0);
        server_address_1.sun_family = AF_UNIX;
        
        strcpy(server_address_1.sun_path, "server_socket_1");
        server_len_1 = sizeof(server_address_1);
        
        bind(server_sockfd_1, (struct sockaddr*) &server_address_1, server_len_1);
        
        while(1)
        {
            printf("Server 1 is waiting...\n");
            listen(server_sockfd_1, 5);     //Socket 1 listening
        
        	int answer;
        
            //Socket 1
            client_len_1 = sizeof(client_address_1);
            client_sockfd_1 = accept(server_sockfd_1, (struct sockaddr*) &client_address_1, &client_len_1);

            read(client_sockfd_1, &answer, sizeof(int));
            
            printf("We've got %i from client\n", answer);
        }
        
        close(client_sockfd_1);
    }


    return 0;
}