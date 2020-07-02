#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct msgbuf{
	long msgtype;
	char mtext[20];
};

int main(void){
	key_t key_id;
	int i=0;
	struct msgbuf sndbuf;

	//create message queue
	key_id = msgget((key_t)1234, IPC_CREAT|0666);
	if(key_id == -1){
		perror("msgget error : ");
		return 0;
	}

	while(1){
		//data initialize
		sndbuf.msgtype = 3;
		fgets(sndbuf.mtext, sizeof(sndbuf.mtext), stdin);
		sndbuf.mtext[strlen(sndbuf.mtext) - 1] = '\0';
		//put message in message queue
		if(msgsnd(key_id, (void *)&sndbuf, sizeof(struct msgbuf), IPC_NOWAIT) == -1){
			perror("msgsnd error: ");
		}
		if(strcmp(sndbuf.mtext, "quit") == 0) return 0;	
		printf("Sending %dth message is succeed\n", i);
		i++;
	}
	return 0;
}