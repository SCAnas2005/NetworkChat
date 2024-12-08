
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../include/util.h"
#include "../include/addr.h"
#include "../include/connection.h"
#include "../include/stream.h"

int main(int argc, char *argv[])
{
    int sockfd, new_sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr);
    char client_name[MAX_NAME_LENGTH], server_name[MAX_NAME_LENGTH];
    char buffer_error[200], buffer_info[200];
    char buffer_ip[16], buffer_message[MAX_BUFFER_LENGTH];
    int port;
    GetSendMessageArgs args;
    pthread_t thread_id[2];
    int *thread_return[2];

    if (argc != 3)
    {
        usage(argv[0]);
    }
    strcpy(buffer_ip, argv[1]);
    port = atoi(argv[2]);

    sockfd = CreateSocket();
    SetAddrIPv4(&server_addr, buffer_ip, port);

    ConnectClient(sockfd, &server_addr);

    AskName(client_name, DEFAULT_NAME_CLIENT);
    SendName(sockfd, client_name, strlen(client_name));
    GetName(sockfd, server_name, MAX_NAME_LENGTH, DEFAULT_NAME_SERVER);

    printf("\tComunicating with : %s\n", server_name);

    printf("\n\n==================================\n");
    while(1)
    {
        args.sockfd = sockfd;
        args.buffer_message = buffer_message; 
        args.size = MAX_BUFFER_LENGTH;
        args.name = server_name;

        pthread_create(&thread_id[0], NULL, (void *)GetAndPrintMessage, 
        (void *)&args);                
        pthread_create(&thread_id[1], NULL, (void *)ReadAndSendMessage, 
        (void *)&args);


        pthread_join(thread_id[0], (void *)&thread_return[0]);
        pthread_join(thread_id[1], (void *)&thread_return[1]);
    }
    printf("\n==================================\n\n");

    info("Disconected...");

    return EXIT_SUCCESS;
}