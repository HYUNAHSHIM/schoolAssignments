#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	
	int i=0;

	if(argc!=2){return 0;}
	else{
		int num=atoi(argv[1]);
		char **arr;
		arr	= (char**) malloc (sizeof(char*) * num);
		
		for(i=0; i<num; i++){
			arr[i]=(char*)malloc(sizeof(char)*30);
		}

		printf("enter %d names:\n",num);

		for(i=0; i<num; i++){
			scanf("%s",arr[i]);
		}

		printf("the names you entered:\n");

		for(i=0;i<num;i++){
			printf("%s\n",arr[i]);
		}
	

		for(i=0;i<num;i++){
			free(arr[i]);
		}
		free(arr);
		}
	return 0;
}


