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


//or



#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t waiting_room_mutex;
sem_t barber_room_mutex;
sem_t barber_chair_free;
sem_t barber;
sem_t customers;
sem_t cutting;

int waiting_chairs_free = 3;
int barber_room_chairs_free = 3;

int barber_chair_states[3]={0};

void* customer(){
        sem_wait(&waiting_room_mutex);
        if(waiting_chairs_free==0){
                printf("Waiting room full! Leaving\n");
                sem_post(&waiting_room_mutex);
                return NULL;
        }
        waiting_chairs_free--;
        sem_post(&waiting_room_mutex);

        while(1){
                sem_wait(&barber_room_mutex);
                if(barber_room_chairs_free==0){
                        sem_post(&barber_room_mutex);
                        continue;
                }
                sem_wait(&waiting_room_mutex);
                waiting_chairs_free++;
                sem_post(&waiting_room_mutex);
                barber_room_chairs_free--;
                sem_post(&barber_room_mutex);
                break;
        }
        sem_post(&customers);
        sem_wait(&barber);
        printf("Starting haircut\n");
        sleep(1); /* hair cut */
        printf("Ending haircut\n");
        sem_post(&cutting);
        return NULL;
}

void* barber_fn(){
        while(1){
                sem_wait(&customers);
                sem_wait(&cutting);
                sem_wait(&barber_room_mutex);
                barber_room_chairs_free++;
                sem_post(&barber_room_mutex);
                sem_post(&barber);
        }
}

int main(){
        sem_init(&waiting_room_mutex, 0, 1);
        sem_init(&barber_room_mutex, 0, 1);
        sem_init(&barber, 0, 1);
        sem_init(&customers, 0, 0);
        sem_init(&cutting, 0, 0);

        pthread_t b, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10;

        pthread_create(&b, NULL, barber_fn, (void*)&b);
        pthread_create(&c1, NULL, customer, (void*)&c1);
        pthread_create(&c2, NULL, customer, (void*)&c2);
        pthread_create(&c3, NULL, customer, (void*)&c3);
        pthread_create(&c4, NULL, customer, (void*)&c4);
        sleep(2);
        pthread_create(&c5, NULL, customer, (void*)&c5);
        pthread_create(&c6, NULL, customer, (void*)&c6);
        pthread_create(&c7, NULL, customer, (void*)&c7);
        pthread_create(&c8, NULL, customer, (void*)&c8);
        pthread_create(&c9, NULL, customer, (void*)&c9);
        pthread_create(&c10, NULL, customer, (void*)&c10);

        pthread_join(c1,NULL);
        pthread_join(c2,NULL);
        pthread_join(c3,NULL);
        pthread_join(c4,NULL);
        pthread_join(c5,NULL);
        pthread_join(c6,NULL);
        pthread_join(c7,NULL);
        pthread_join(c8,NULL);
        pthread_join(c9,NULL);
        pthread_join(c10,NULL);
}
