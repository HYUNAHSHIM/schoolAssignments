#include <iostream>
using namespace std;

void sort(int* arr2, int n2) {
	for(int i=0; i<n2; i++){
		for (int j= i+1; j<n2; j++){
			if (arr2[i]> arr2[j]){
				int a = arr2[j];
				arr2[j] =arr2[i];
				arr2[i] =a;
			}
		}
	}
	for(int i=0; i<n2; i++){
		cout << arr2[i] << " ";
	}
	cout << "\n";
}

int main(){
	int n=0;
	cin >> n;
	if(n<=0){
		return 0;
	}
	int*arr = new int[n];

	for (int i=0; i<n; i++){
		cin >> arr[i];
	}
	sort(arr,n);
	delete[] arr;
	return 0;
}

