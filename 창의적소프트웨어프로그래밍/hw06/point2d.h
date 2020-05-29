#ifndef __hw06__point2d__
#define __hw06__point2d__
#include <iostream>

using namespace std;

class Point {
public:	
	int x_, y_;


	void point(Point p) {
		cout << "(" << x_ << ", " << y_ <<")"<< endl;
	}
	
	void point2(int x, int y) {
		x_ = x;
		y_ = y;
	}

	Point operator-() const {
		
	}
}; 

	Point operator+(const Point& lhs, const Point& rhs); 
	Point operator-(const Point& lhs, const Point& rhs); 
	Point operator*(const Point& lhs, const Point& rhs);






#endif
