#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main(void){
	int shmid;
	int i;
	void *shmaddr;
	int ret;
	//make a shared memory
	shmid = shmget((key_t)1234, 1024, IPC_CREAT|0666);
	if(shmid < 0){
		perror("shmget");
		return 0;
	}
	//attach the shared memory
	shmaddr = shmat(shmid, (void *)0, 0);
	if(shmaddr == (char *)-1){
		perror("attach failed\n");
		return 0;
	}
	while(1){
		char msg[1024];
		fgets(msg, sizeof(msg), stdin);
		strcpy((char *)shmaddr, msg);
		msg[strlen(msg) - 1] = '\0';
		if(!strcmp(msg, "quit")) break;
	}

	//detach the shared memory
	ret = shmdt(shmaddr);
	if(ret == -1){
		perror("detach failed\n");
		return 0;
	}
	return 0;
}