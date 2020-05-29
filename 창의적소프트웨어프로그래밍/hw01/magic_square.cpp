#include <iostream>
using namespace std;

void Magic_Square(int** arr2, int num2){
	int a=0, b=(num2-1)/2;
	arr2[a][b]=1;
	for(int i=2;i<num2*num2+1; i++){
		if((a-1)>=0 &&(b+1) <=(num2-1)&& arr2[a-1][b+1]==0){
			a--;
			b++;
			arr2[a][b]=i;
		}
		else if ((a-1)<0&& (b+1)<=(num2-1)&&arr2[a+num2-1][b+1]==0){
				a=a+num2-1;
				b++;
				arr2[a][b]=i;
				}
		else if ((a-1)>=0&&(b+1)> (num2-1)&& arr2[a-1][b-num2+1]==0){
				a--;
				b=b-num2+1;
				arr2[a][b]=i;
				}
		else if ((a-1)<0&&(b+1)>(num2-1)&&arr2[a+num2-1][b-num2+1]==0){
				a=a+num2-1;
				b=b-num2+1;
				arr2[a][b]=i;
				}
		else {
			a--;
			arr2[a][b]=i;
	}
	}
	for(int i=0; i<num2; i++){
		for(int j=0; j<num2;j++){
				if(j%(num2)==0){
				cout << "\n";
			}
				cout << arr2[i][j] << " ";
		}
}	
	cout << "\n";
}

int main()
{
	int num=0;
	int** arr;
	cin >> num;
	if(num%2==0||num<=0){
		return 0;
	}
	else {
		arr= new int*[num];
		for (int i=0; i<num; i++){
			arr[i] =new int[num];
		}
		for(int i=0; i<num; i++){
			for(int j=0; j<num; j++){
				arr[i][j]=0;
			}
		}
		Magic_Square(arr, num);
	}
	for( int i=0; i<num; i++){
		delete[] arr[i];
	}
	delete[] arr;
	return 0;
}


