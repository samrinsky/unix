#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Let us create a global variable to change it in threads
int g = 0;

// The function to be executed by all threads
void *myThreadFun(void *vargp)
{
    int a=10;
    // Store the value argument passed to this thread
    int *myid = (int *)vargp;

    // Let us create a static variable to observe its changes
    static int s = 0;

    // Change static and global variables
    ++s; ++g; ++a;

    // Print the argument, static and global variables
    printf("Thread ID: %d, Static: %d, Global: %d  Local: %d \n", *myid, ++s, ++g, ++a);
        ++a;
}


    
int main()
{
    int i;
    pthread_t tid1,tid2,tid3;

    // Let us create three threads
    pthread_create(&tid1, NULL, myThreadFun, (void *)&tid1);
    pthread_create(&tid2, NULL, myThreadFun, (void *)&tid2);
    pthread_create(&tid3, NULL, myThreadFun, (void *)&tid3);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    return 0;
}
