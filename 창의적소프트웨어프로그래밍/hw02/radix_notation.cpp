#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

string RadixNotation(unsigned int number, unsigned int radix);

int main(int argc, char** argv){
	if (argc<2){
		return -1;
	}
	unsigned int radix;
	sscanf(argv[1], "%u", &radix);

	if (radix<2 || radix>36){
		return -1;
	}
	for(int i=2; i<argc; ++i){
		unsigned int number;
		sscanf(argv[i], "%u", &number);
		cout << RadixNotation(number, radix) << endl;
	}
	return 0;
}

string RadixNotation(unsigned int number, unsigned int radix) {

	char *arr;
	int i=0;

	for(i; number>=radix; i++){
		if  (number % radix<10){
			*(arr+i)=(number % radix)+'0';
		}
		else{
			*(arr+i)=(number% radix) +87+'\0';
		}
		number/= radix;
	}
	if(number%radix<10){
		*(arr+i)=number+'0';}
	else{
		*(arr+i)=(number%radix)+87+'\0';}

	*(arr+i+1)='\0';
	
	int len=0;
	int k=0;
	int m=0;
	char tmp;
	while(*(arr+k++) != '\0'){
		len++;}
	m=len/2;
	for(k=0;k<m;k++){
		tmp=*(arr+k);
		*(arr+k)=*(arr+(len-1-k));
		*(arr+len-1-k)=tmp;
	}
	return arr;
}

