#include <iostream>
using namespace std;
int fib(int n){
	if(n<2){
		return n;
	}
	else{
		return fib(n-1)+fib(n-2);
	}
}

int  main()
{
	int result=0;
	int num=0;
	cin >> num;
	if(num<0){
		return 0;
	}
	for(int i=1; i<=num;i++){
		result=fib(i);
		cout << fib(i) <<" ";
	}
cout<<"\n";
return 0;
}

	
