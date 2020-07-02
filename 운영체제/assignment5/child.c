#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define COUNTING_NUMBER 2000000

typedef struct smStruct{
	int processidassign;
	int turn;
	int flag[2];
	int critical_section_variable;
}smStruct;

smStruct *smstruct;
int ID;

void lock(){
	smstruct->flag[ID] = 1;
	smstruct->turn = 1-ID;
	while(smstruct->flag[1-ID] == 1 && smstruct->turn == 1-ID);
}

void unlock(){
	smstruct->flag[ID] = 0;
}

int main(int argc, char *argv[]){
	int smid;
	void *smaddr;
	int ret;
	int i;
	int localcount = 0;

	//get shared memory id
	smid = shmget((key_t)1234, 1024, IPC_CREAT|0666);
	if(smid == -1){
		perror("shamred memory access is failed\n");
		return 0;
	}

	//attach the shared memory
	smaddr = shmat(smid, (void *)0, 0);
	if(smaddr == (char *)-1){
		perror("attach failed\n");
		return 0;
	}

	//get smStruct
	smstruct = (smStruct *)smaddr;
	ID = atoi(argv[0]);
	printf("Myorder = %d, process pid = %d\n", ID, getpid());

	for(i=0; i<COUNTING_NUMBER; i++){
		localcount++;
		//lock
		lock();
		//critical section
		smstruct->critical_section_variable += 1;
		//unlock
		unlock();
	}

	// print
	printf("child finish! local count = %d\n", localcount);
	
	//detach the shared memory
	ret = shmdt(smaddr);
	if(ret == -1){
		perror("detach failed\n");
		return 0;
	}

	return 0;
}