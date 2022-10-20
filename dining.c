/* program diningphilosophers */ semaphore fork [5] = {1};
int i;
void philosopher (int i)
{
}
     while (true) {
think();
wait (fork[i]);
wait (fork [(i+1) mod 5]); eat();
signal(fork [(i+1) mod 5]); signal(fork[i]);
}
void main()
{
parbegin (philosopher (0), philosopher (1), philosopher (2), philosopher (3), philosopher (4));
}

//or

semaphore fork[5] = {1}; semaphore room = {4};
int i;
void philosopher (int i) {
     while (true) {
think();
wait (room);
wait (fork[i]);
wait (fork [(i+1) mod 5]); eat();
signal (fork [(i+1) mod 5]); signal (fork[i]);
signal (room);
} }
void main() {
  parbegin (philosopher (0), philosopher (1), philosopher (2), philosopher (3), philosopher (4));
}


//or

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#define N 5  //3 states
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (philosopherNumber + 4)%N
#define RIGHT (philosopherNumber + 1)%N
int state[N];
int philosophers[N] = {0, 1, 2, 3, 4}; //5 philosophers
sem_t mutex; //access critical section
sem_t S[N];  //shared variable
void test(int philosopherNumber)
{
    if (state[philosopherNumber] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        //state that eating only if both neighbors are not eating
        state[philosopherNumber] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n", philosopherNumber + 1, LEFT + 1, philosopherNumber + 1);
        printf("Philosopher %d is Eating\n", philosopherNumber + 1);
        //sem_post(&S[philosopherNumber]) has no effect during takefork
        //used to wake up hungry philosophers during putfork
        sem_post(&S[philosopherNumber]);
    }
}

//take up chopsticks
void pickup(int philosopherNumber)
{
    //access critical section
    sem_wait(&mutex);
    //state that hungry
    state[philosopherNumber] = HUNGRY;
    printf("Philosopher %d is Hungry\n", philosopherNumber + 1);

    //eat if neighbours are not eating
    test(philosopherNumber);
    //leave critical section
    sem_post(&mutex);

    //if unable to eat wait to be signalled
    sem_wait(&S[philosopherNumber]);
    sleep(1);
}


//put down chopsticks
void putdown(int philosopherNumber)
{
    //access critical section
    sem_wait(&mutex);
    // state that thinking
    state[philosopherNumber] = THINKING;
    printf("Philosopher %d putting", philosopherNumber + 1);
	printf(" fork %d and %d down\n", LEFT + 1, philosopherNumber + 1);
    printf("Philosopher %d is thinking\n", philosopherNumber + 1);
    test(LEFT);
    test(RIGHT);
    //leave critical section
    sem_post(&mutex);
}

void *philospher(void *num)
{
    while(1)
    {
        int *i = num;
        sleep(1);
        pickup(*i);
        sleep(0);
        putdown(*i);
    }
}

int main()
{
    int i;
    pthread_t thread_id[N];
    // initialize the semaphores
    sem_init(&mutex, 0, 1);
    for(i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);
    for(i = 0; i < N; i++)
    {
        // create philososopher processes
        pthread_create(&thread_id[i], NULL, philospher, &philosophers[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }
    for(i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
    return 0;
}
