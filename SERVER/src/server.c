

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../../include/util.h"
#include "../../include/addr.h"
#include "../include/interact.h"
#include "../../include/connection.h"
#include "../../include/stream.h"

int main(int argc, char *argv[])
{
    int sockfd, new_sockfd, bytes_recv;
    int close = 0;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr);
    char buffer_client[MAX_BUFFER_LENGTH], buffer_info[200];
    char server_name[MAX_NAME_LENGTH], client_name[MAX_NAME_LENGTH];
    char buffer_client_message[MAX_BUFFER_LENGTH+100];
    int port, *thread_return[2];
    char buffer_ip[16];
    int connected = 0;

    pthread_t thread_id[2];             // thread id for send and recv data
    GetSendMessageArgs args;

    if (argc != 3)
    {
        usage(argv[0]);
    }
    port = atoi(argv[2]);
    strcpy(buffer_ip, argv[1]);


    sockfd = CreateSocket();                          // Create socket TCP IP
    SetAddrIPv4(&serv_addr, argv[1], port);  // Config server sock address 

    StartServer(sockfd, &serv_addr);       // Starting the server 


    printf("\n");
    AskName(server_name, DEFAULT_NAME_SERVER);          // Get the server name string

    while (!close)
    {
        new_sockfd = AcceptConnection(sockfd, &client_addr);
        connected = 1;
        GetName(new_sockfd, client_name, MAX_NAME_LENGTH, DEFAULT_NAME_CLIENT);
        SendName(new_sockfd, server_name, strlen(server_name));

        printf("\tComunicating with : %s\n", client_name);


        printf("\n\n==================================\n");
        while(1)
        {
            args.sockfd = new_sockfd;
            args.buffer_message = buffer_client_message; 
            args.size = MAX_BUFFER_LENGTH;
            args.name = client_name;

            pthread_create(&thread_id[0], NULL, (void *)GetAndPrintMessage, 
            (void *)&args);                
            pthread_create(&thread_id[1], NULL, (void *)ReadAndSendMessage, 
            (void *)&args);


            pthread_join(thread_id[0], (void *)&thread_return[0]);
            pthread_join(thread_id[1], (void *)&thread_return[1]);
        }       
        printf("|\n==================================\n\n");


        sprintf(buffer_info, "%s (%s|%d)disconnected.", 
        client_name, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        info(buffer_info);

        WantToQuit(&close);
        ClearBuffer();
    }

    info("Server shutdown");

    return EXIT_SUCCESS;
}
