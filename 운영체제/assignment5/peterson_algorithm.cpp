#include <atomic>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define COUNTING_NUMBER 2000000

using namespace std;

int critical_section_variable = 0;
//int turn = 0;
//int flag[2] = {0, 0};

atomic_int turn(0);
atomic_int flag0(0), flag1(0);

void lock(int self){
    if(self == 0){
        flag0++;
        turn = 1;
        while(flag1 == 1 && turn == 1);
    }
    else if(self == 1){
        flag1++;
        turn = 0;
        while(flag0 == 1 && turn == 0);
    }
    //flag[self] = 1;
    //turn = 1-self;
    //while(flag[1-self] == 1 && turn == 1-self);
}

void unlock(int self){
    if(self == 0){
        flag0 = 0;
    }
    else if(self == 1){
        flag1 = 0;
    }
    //flag[self] = 0;
}

void* func(void *s){
    int* thread_num = (int *)s;
    int i;
    for(i=0; i<COUNTING_NUMBER; i++){
        lock(*thread_num);
        critical_section_variable++;
        unlock(*thread_num);
    }
}

int main(void){
    pthread_t p1, p2;
    int parameter[2] = {0, 1};
    
    pthread_create(&p1, NULL, func, (void*)&parameter[0]);
    pthread_create(&p2, NULL, func, (void*)&parameter[1]);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("Actual Count: %d | Expected Count: %d\n", critical_section_variable, COUNTING_NUMBER*2);

    return 0;
}
