
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include "../include/addr.h"



void SetAddrIPv4(struct sockaddr_in *addr, char *ip, int port)
{
    addr->sin_family = AF_INET;
    inet_aton(ip, &addr->sin_addr);
    addr->sin_port = htons(port);
    bzero(addr->sin_zero, 8);
}