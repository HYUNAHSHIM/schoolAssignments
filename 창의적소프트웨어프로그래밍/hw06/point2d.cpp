#include <iostream>
#include "point2d.h"

using namespace std;


Point operator+(const Point& lhs, const Point& rhs) {
	class Point j;

	j.x_=lhs.x_ + rhs.x_;
	j.y_ = lhs.y_ + rhs.y_;

	return j;
}

Point operator-(const Point& lhs, const Point& rhs) {
	class Point k;

	k.x_ = lhs.x_ - rhs.x_;
	k.y_ = lhs.y_ - rhs.y_;

	return k;
}

Point operator*(const Point& lhs, const Point& rhs) {
	class Point h;

	h.x_ = lhs.x_ * rhs.x_;
	h.y_ = lhs.y_ * rhs.y_;

	return h;
}
