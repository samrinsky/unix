#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>
#include<unistd.h>
#include<string.h>

sem_t bmutex;
int count=0;
void* barber(void *arg)
{
        int f;
        f=((int)arg);
        count=count+1;
        if(count>0 && count<6){
                printf("\nCustomer %d is waiting \n",f);
                while(count>0){
                sem_wait(&bmutex);
                printf("\nCustomer %d has arrived \n",f);
                sleep(4);
                count=count-1;
                printf("\nCustomer %d is exiting \n",f);
                sem_post(&bmutex);
                pthread_exit((void *)&arg);
                }
        }
        else{
                printf("\nCustomer %d has no accomodation \n",f);
                exit(1);
        }

}


int main(){

        sem_init(&bmutex,0,1);
        pthread_t cust[6];
        for(int i=0;i<6;i++){
                pthread_create(&cust[i],NULL,barber,(void *)i);
                sleep(2);
        }
        for(int i=0;i<6;i++){
               pthread_join(cust[i],NULL);
        }
        sem_destroy(&bmutex);


}
