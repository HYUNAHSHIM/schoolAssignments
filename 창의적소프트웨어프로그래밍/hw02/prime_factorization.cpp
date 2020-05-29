#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

string primeFactorization(unsigned int _number){
	int a=2, b=0;
	string answer;
	for(int i=2;i<=_number; i++){
		if(_number %i==0){
			_number /=i;
			answer +=to_string(i);
			if(a==i){
				b+=1;
				int length = answer.length();
				answer.erase(length-1, length);
				if(_number %i!=0){
					answer += to_string(i) + "^" + to_string(b)+"x";
					b=0;
					a=i+1;}
				i=1;}
			else{
				b+=1;
				answer += "^"+to_string(b)+"x";
				i=1;}
		}
		if(_number ==1){
			int length = answer.length();
			answer.erase(length-3,length);
		}
	}
	return answer;
}
int main(int argc, char** argv){
	if(argc<1){
		return -1;}
	unsigned int number;
	sscanf(argv[1],"%u", &number);
	cout << primeFactorization(number) << endl;
	return 0;}
