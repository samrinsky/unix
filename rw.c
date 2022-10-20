#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex,writeblock;
int data = 0,rcount = 0;

void *reader(void *arg)
{
        int f;
        f = ((int)arg);
        sem_wait(&mutex);
        rcount = rcount + 1;
        printf("\nReader %d has arrived \n",f);
        if(rcount==1)
                sem_wait(&writeblock);
        sem_post(&mutex);
        printf("\nReader Entered %d Data read by the reader is %d\n",f,data);
        sleep(4);
        sem_wait(&mutex);
        rcount = rcount - 1;
        printf("\nReader Exiting : %d Remaining Readers:%d \n",f,rcount);

        if(rcount==0)
        {
                printf("\nNo readers Writers can write\n");
                sem_post(&writeblock);
        }
        sem_post(&mutex);
}

void *writer(void *arg)
{
        int f;
        f = ((int) arg);
        printf("\nWriter %d has arrived\n",f);
        sem_wait(&writeblock);
        data++;
        printf("\nWriter Entered %d Data writen by the writer is %d\n",f,data);
        sleep(2);
        printf("\nWriter Exiting : %d\n",f);
        sem_post(&writeblock);
}
main()
{
        int i,b;
        pthread_t rtid[5],wtid[5];
        sem_init(&mutex,0,1);
        sem_init(&writeblock,0,1);
        for(i=0;i<=2;i++)
        {
                pthread_create(&wtid[i],NULL,writer,(void *)i);
                sleep(2);
                pthread_create(&rtid[i],NULL,reader,(void *)i);
        }
        for(i=0;i<=2;i++)
        {
                pthread_join(wtid[i],NULL);
                pthread_join(rtid[i],NULL);
        }
}
