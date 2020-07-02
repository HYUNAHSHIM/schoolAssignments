#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define COUNTING_NUMBER 2000000

// struct for shared memory
typedef struct smStruct{
	int processidassign;
	int turn;
	int flag[2];
	int critical_section_variable;
}smStruct;

int main(void){
	int status1, status2;
	pid_t pid1, pid2;
	void *smaddr;
	int smid;
	int ret;
	smStruct *smstruct = malloc(sizeof(smStruct));

	// make a shared memory
	smid = shmget((key_t)1234, 1024, IPC_CREAT|0666);
	if(smid < 0){
		perror("shmget error\n");
		return 0;
	}
	// attach the shared memory
	smaddr = shmat(smid, (void *)0, 0);
	if(smaddr == (char *)-1){
		perror("failed attach address\n");
		return 0;
	}
	smstruct = smaddr;
	smstruct->turn = 0;
	smstruct->processidassign = 0;
	smstruct->flag[0] = 0;
	smstruct->flag[1] = 0;
	smstruct->critical_section_variable = 0;

	pid2 = fork();
	if(pid2 == 0){// second child process
		const char *tmp = "1";
		execl("./child", tmp, NULL);
	}
	else{
		pid1 = fork();
		if(pid1 == 0){// first child process
			const char *tmp = "0";
			execl("./child", tmp, NULL);
		}
		else{// parent process
			waitpid(pid1, &status1, 0);
			waitpid(pid2, &status2, 0);

			//  print the result
			printf("Actual Count: %d | Expected Count: %d\n", smstruct->critical_section_variable, COUNTING_NUMBER * 2);

			//remove the shared memory
			ret = shmctl(smid, IPC_RMID, 0);
			if(ret == -1){
				perror("remove failed\n");
				return 0;
			}
		}

	}
	return 0;
}