#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARGUMENT_NUMBER 20

long long result=0;

void *ThreadFunc(void *n){
	long long i;
	long long number = *((long long *)n);
	//variable for calculate in each thread
	long long tmp = 0;
	printf("number = %lld\n", number);
	for(i=0;i<25000000;i++) tmp += number;
	//return value which will be returned to pthread_join function
	return (void *)tmp;
}

int main(void){
	pthread_t threadID[ARGUMENT_NUMBER];
	long long argument[ARGUMENT_NUMBER];
	long long i;
	long long ret;

	//initialize arguments
	for(i=0; i<ARGUMENT_NUMBER; i++) argument[i] = i;
	//create threads with argument
	for(i=0; i<ARGUMENT_NUMBER; i++) pthread_create(&(threadID[i]), NULL, ThreadFunc, (void*)&argument[i]);
	//print at main thread
	printf("Main Thread is waiting for Child Thread!\n");
	//finish threads with return value ret
	//add ret of each thread to result
	for(i=0; i<ARGUMENT_NUMBER; i++) {
		pthread_join(threadID[i], (void **)&ret);
		result += ret;
	}
	//print final result
	//this value will not change
	printf("result = %lld\n", result);
	return 0;
}