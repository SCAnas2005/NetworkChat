
#ifndef __UTIL__C__
#define __UTIL__C__

    #define MAX_BUFFER_LENGTH 1000
    #define MAX_NAME_LENGTH 50
    #define DEFAULT_NAME_SERVER "Server"
    #define DEFAULT_NAME_CLIENT "Client"

    typedef struct 
    {
        int sockfd;
        char *buffer_message;
        int size;
        char *name;
    } GetSendMessageArgs;


    void fatal(char *message);
    void info(char *message);
    void usage(char *filename);

    void ClearBuffer();
    void PrintArgs(GetSendMessageArgs args);

#endif