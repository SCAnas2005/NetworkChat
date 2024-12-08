
#ifndef __STREAM__C__
#define __STREAM__C__

    int GetMessage(int sockfd, char *buffer_message, int size);
    int SendMessage(int sockfd, char *buffer_message, int size);
    void PrintMessage(char *buffer_message, char *name);

    void WantToQuit(int *close);
    int IsGoodName(char *name_buffer);
    void AskName(char *name_buffer, char *default_name);
    void GetName(int sockfd, char *name_buffer, int size, char *default_name);
    void SendName(int sockfd, char *name, int size);

    int ReadConsole(char *buffer_message, int size);

    int GetAndPrintMessage(void *data);  // using thread !
    int ReadAndSendMessage(void *data);  // Using Thread

#endif