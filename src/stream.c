
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "../include/stream.h"
#include "../include/util.h"

int GetMessage(int sockfd, char *buffer_message, int size)
{
    int bytes_received;
    bytes_received = recv(sockfd, buffer_message, size, 0);
    buffer_message[bytes_received] = 0;
        
    if (bytes_received == -1 || bytes_received == 0)
        return 0;
    return 1;
}

int SendMessage(int sockfd, char *buffer_message, int size)
{
    int bytes_sent;
    bytes_sent = send(sockfd, buffer_message, size, 0);

    return (bytes_sent != -1);
}

void PrintMessage(char *buffer_message, char *name)
{
    char print_buffer[MAX_BUFFER_LENGTH+MAX_NAME_LENGTH+10];

    sprintf(print_buffer, "\n|\t\t[%s] : '%s'", name, buffer_message);
    puts(print_buffer);
}

void WantToQuit(int *close)
{
    char res;
    printf("Do you want to quit ? (y/N) ");
    res = fgetc(stdin);

    if (res == 'y' || res == 'Y')
        *close = 1;
    else if (res == 'n' || res == 'N')
        *close = 0;
    else
    {
        ClearBuffer();
        WantToQuit(close);
    }
}

void AskName(char *name_buffer, char *default_name)
{
    printf("What's your name : ");
    fgets(name_buffer, MAX_NAME_LENGTH, stdin);

    if (IsGoodName(name_buffer))
    {
        if (name_buffer[0] == '\n')
            strcpy(name_buffer, default_name);
        else
            name_buffer[strlen(name_buffer)-1] = 0;
    }
    else
    {
        ClearBuffer();
        AskName(name_buffer, default_name);
    }
}

int IsGoodName(char *name_buffer)
{
    if (name_buffer == NULL)    
        return 0;

    if (name_buffer[0] == 0)
        return 0;

    if (strlen(name_buffer) < 1)
        return 0;

    return 1;
}


void GetName(int sockfd, char *name_buffer, int size, char *default_name)
{
    int bytes = recv(sockfd, name_buffer, size, 0);
    if (bytes == 0 || bytes == -1 || name_buffer[0] == '\n')
    {
        strcpy(name_buffer, default_name);
    } 
    else
        name_buffer[bytes] = 0; 
}



void SendName(int sockfd, char *name, int size)
{
    if (send(sockfd, name, size, 0) == -1)
        fatal("SendName() failed");
}


int ReadConsole(char *buffer_message, int size)
{
    printf("|\tMessage: ");
    fgets(buffer_message, size, stdin);

    buffer_message[strlen(buffer_message)-1] = 0;
}


int GetAndPrintMessage(void *data)  // using thread !
{   // args : int sockfd, char *buffer_message, int size, char *name
    GetSendMessageArgs args = *(GetSendMessageArgs*)data;
    PrintArgs(args);

    while (1)
    {
        if (!GetMessage(args.sockfd, args.buffer_message, args.size))
            return 0;
        PrintMessage(args.buffer_message, args.name);
    }
    
    return 1;
}

int ReadAndSendMessage(void *data)  // Using Thread
{   // args : int sockfd, char *buffer_message, int size
    GetSendMessageArgs args = *(GetSendMessageArgs*)data;
    PrintArgs(args);

    while (1)
    {
        ReadConsole(args.buffer_message, args.size);
        if (!SendMessage(args.sockfd, args.buffer_message, strlen(args.buffer_message)))
            return 0;
    }

    return 1;
}