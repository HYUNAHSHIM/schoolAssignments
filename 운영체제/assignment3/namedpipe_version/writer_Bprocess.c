#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MSG_SIZE 80
#define PIPENAME "./named_pipe_file"

int main(void){
	char msg[MSG_SIZE];
	int fd;
	int ret,i;

	//open the named pipe
	fd = open(PIPENAME, O_WRONLY);
	if(fd < 0){
		printf("Open failed\n");
		return 0;
	}
	while(1){
		sleep(1);
		fgets(msg, sizeof(msg), stdin);
		msg[strlen(msg) - 1] = '\0';
		ret = write(fd, msg, sizeof(msg));
		if(ret < 0){
			printf("Write failed\n");
			return 0;
		}
		if(!strcmp(msg, "quit")) return 0;
	}
	return 0;
}