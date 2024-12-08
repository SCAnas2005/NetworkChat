
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

#include "../include/connection.h"
#include "../include/util.h"

int CreateSocket()
{
    int sockfd, reuse = 1;

    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        fatal("socket() failed");
    }

    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse,
    sizeof(reuse)) < 0)
    {
        fatal("setsockopt() failed");
    }

    return sockfd;
}

void StartServer(int sockfd, struct sockaddr_in* serv_addr)
{
    socklen_t addr_len = sizeof(struct sockaddr); 
    char buffer_info[200];
    if (bind(sockfd, (const struct sockaddr *)serv_addr, addr_len) == -1)
        fatal("Server failed to start (bind())");
    
    sprintf(buffer_info, "Server binded at %s|%d", 
    inet_ntoa(serv_addr->sin_addr), ntohs(serv_addr->sin_port));
    info(buffer_info);

    if (listen(sockfd, 10) == -1)
        fatal("Server failed to start (listen())");

    sprintf(buffer_info, "Server listening at port %d", 
    ntohs(serv_addr->sin_port));
    info(buffer_info);


    info("Server started");
}

int AcceptConnection(int sockfd, struct sockaddr_in *client_addr)
{
    int new_sockfd; 
    socklen_t addr_size = sizeof(struct sockaddr_in);
    char buffer_info[200];

    new_sockfd = accept(sockfd, (struct sockaddr *)client_addr, &addr_size);
    if (new_sockfd == -1)
    {
        sprintf(buffer_info, "Connection to %s|%d failed.", 
        inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port));

        fatal(buffer_info);
    }

    sprintf(buffer_info, "Connection open %s|%d", 
    inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port));
    info(buffer_info);

    return new_sockfd;
}

void ConnectClient(int sockfd, struct sockaddr_in *serv_addr)
{
    int res;
    char buffer_info[200];
    socklen_t addr_len = sizeof(struct sockaddr_in);


    sprintf(buffer_info, "Connection to %s|%d.\n", 
    inet_ntoa(serv_addr->sin_addr), ntohs(serv_addr->sin_port));
    info(buffer_info);


    res = connect(sockfd, (struct sockaddr*)serv_addr, addr_len);
    if (res == -1)
    {
        sprintf(buffer_info, "Connection to %s|%d failed", 
        inet_ntoa(serv_addr->sin_addr), ntohs(serv_addr->sin_port));

        fatal(buffer_info);
    }

    info("Connected");
}