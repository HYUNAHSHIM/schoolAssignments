#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <unistd.h>
  
#define N 6 
#define LEFT (phnum + 5) % N 
#define RIGHT (phnum + 1) % N 
  
int state[N]; //0=eating, 1=hungry, 2=thinking
int phil[N] = { 0, 1, 2, 3, 4, 5 }; 
  
sem_t mutex; 
sem_t chopstick[N]; 
  
void test(int phnum){ 
    if(state[phnum] == 1){
        //if even
        if(phnum % 2 == 0){
            sem_wait(&chopstick[phnum]);
            printf("Philosopher %d takes right fork, number %d\n", phnum + 1, phnum + 1);
            sleep(2);
            sem_wait(&chopstick[LEFT]);
            printf("Philosopher %d takes left fork, number %d\n", phnum + 1, LEFT + 1);
            printf("Philosopher %d is eating\n", phnum + 1);
        }
        //if odd
        else{
            sem_wait(&chopstick[LEFT]);
            printf("Philosopher %d takes left fork, number %d\n", phnum + 1, LEFT + 1);
            sleep(2);
            sem_wait(&chopstick[phnum]);
            printf("Philosopher %d takes right fork, number %d\n", phnum + 1, phnum + 1);
            printf("Philosopher %d is eating\n", phnum + 1);
        }
    }
}
  
void* philosopher(void* num){ 
    int i;
    int* n = num;
    int phnum = *n;
    for(i=0;i<5;i++) {
        //take chopstick
        sem_wait(&mutex);
        //state that is hungry
        state[phnum] = 1;
        sem_post(&mutex);
        //eat if neighbors are not eating
        test(phnum);
        sleep(1);
        
        //put chopstick down
        sem_wait(&mutex);
        //state that is thinking
        state[phnum] = 2;
        printf("Philosopher %d finished eating\n", phnum + 1);
        sem_post(&mutex);
        sem_post(&chopstick[phnum]);
        sem_post(&chopstick[LEFT]);
        test(LEFT);
        test(RIGHT);
    } 
} 
  
int main(void){ 
    int i; 
    pthread_t thread_id[N]; 
    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++) sem_init(&chopstick[i], 0, 1); 
    for (i = 0; i < N; i++) pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
    for (i = 0; i < N; i++) pthread_join(thread_id[i], NULL); 
    sem_destory(&mutex);
    for(i = 0; i < N; i++) sem_destory(&chopstick[i]);
    return 0;
} 