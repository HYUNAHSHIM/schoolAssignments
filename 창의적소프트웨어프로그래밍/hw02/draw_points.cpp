#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

using namespace std;
#define MAX_Y 1024
#define MAX_X 1024

int screen[MAX_Y][MAX_X];
int max_x=0, max_y=0;

bool DrawPoint(int x, int y){
	screen[y][x]=1;
	max_x=max_x <x?x: max_x;
	max_y=max_y <y?y: max_y;
	for( int i=0; i<=max_y;i++){
		for(int j=0; j<=max_x;j++){
			if (screen[i][j]==1){
				cout << '*';}
			else {
				cout << '.';}
		}
		cout << '\n';
	}
	return true;
}

int main(void){
	int x;
	int y;
	while(true){
		cin>>x>>y;
		if(x<0||y<0){
			return 0;}
		if(!(DrawPoint(x,y))){
			break;}
	}
}

