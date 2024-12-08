
#ifndef __CONNECTION__C__
#define __CONNECTION__C__

    int CreateSocket();
    void StartServer(int sockfd, struct sockaddr_in* serv_addr);
    int AcceptConnection(int sockfd, struct sockaddr_in *client_addr);
    void ConnectClient(int sockfd, struct sockaddr_in *serv_addr);

#endif