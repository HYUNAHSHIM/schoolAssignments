#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#define COUNTING_NUMBER 100

void *reader();
void *writer();

int cur_writer = 0;
int cur_count = 0;

sem_t s;
sem_t wrt;
int readcount = 0;

int main(void){
	int i;
	sem_init(&s, 0, 1);
	sem_init(&wrt, 0, 1);
	pthread_t r[2];
	pthread_t w[5];
	for(i=0;i<5;i++) pthread_create(&w[i], NULL, (void *)&writer, (void *)&i);
	for(i=0;i<2;i++) pthread_create(&r[i], NULL, (void *)&reader, NULL);
	for(i=0;i<5;i++) pthread_join(w[i], NULL);
	for(i=0;i<2;i++) pthread_join(r[i], NULL);
	sem_destroy(&s);
	sem_destroy(&wrt);
	return 0;
}

void *reader(){
	int i;
	int cw, cc;
	for(i=0;i<COUNTING_NUMBER;i++){
		usleep(30000);
		sem_wait(&s);
		readcount++;
		//in first reader, if writer in critical section wait
		if(readcount == 1) sem_wait(&wrt);
		sem_post(&s);
		cw = cur_writer;
		cc = cur_count;
		printf("The most recent writer id:\t[%d], count:\t[%d]\n", cw, cc);
		//finish critical section;
		sem_wait(&s);
		readcount--;
		if(readcount == 0) sem_post(&wrt);
		sem_post(&s);
	}
}

void *writer(void *n){
	int i, count = 0;
	int *id = (int *)n;
	for(i=0;i<COUNTING_NUMBER;i++){
		usleep(100000);
		sem_wait(&wrt);
		//critical section
		cur_writer = *id;
		count++;
		cur_count = count;
		//finish critical section
		sem_post(&wrt);
	}
}