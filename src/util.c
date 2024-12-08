
#include <stdlib.h>
#include <stdio.h>

#include "../include/util.h"

void fatal(char *message)
{
    printf("[-] Error: %s\n", message); 
    exit(EXIT_FAILURE);
}

void info(char *message)
{
    printf("[+] %s.\n", message);
}

void usage(char *filename)
{
    printf("Usage: %s <ip> <port>", filename);
    exit(EXIT_FAILURE);
}

void ClearBuffer()
{
    char c;
    while (c != EOF && c != '\n')
    {
        c = getchar();
    }
}


void PrintArgs(GetSendMessageArgs args)
{
    printf("args: {%d, %s, %d, %s}\n", args.sockfd, args.buffer_message, args.size, args.name);
}