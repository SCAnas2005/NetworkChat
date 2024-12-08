
#include <stdio.h>
#include <pthread.h>

void a(void *data)
{
    int start = (int) data;
    for (int i = start; i < 20; i++)
    {
        printf("%d\n", i);
    }
}

void b()
{
    for (int i = 0; i < 20; i++)
    {
        printf("%d\n", i);
    }
}

int main(void)
{
    pthread_t thread_id[2];
    int i = 0;

    pthread_create(&thread_id[0], NULL, (void*)a, (void*)i);
    //pthread_create(&thread_id[1], NULL, (void*)b, NULL);


    pthread_join(thread_id[0], NULL);
    //pthread_join(thread_id[1], NULL);

    printf("Size of char* : %d\n", sizeof(int**));

    return 0;
}