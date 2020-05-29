#include <iostream>
#include <string>
#include <vector>
#include "draw_shape.h"

using namespace std;

Canvas::Canvas(size_t row, size_t col)
{
	/*Implement here*/
	this->row_ = row;
	this->col_ = col;
	for (int j = 0; j < row; j++) {

		string str;
		for (int i = 0; i < col; i++) {
			str.push_back('.');
		}
		stage_.push_back(str);
	}
}

Canvas::~Canvas()
{
}

int Canvas::AddShape(const Shape &s)
{
	/*Implement here*/



	int dr_w = (s.width - 1) / 2;
	int dr_h = (s.height - 1) / 2;
	if ((s.y + dr_h) >= row_ || (s.x + dr_w) >= col_) {
		return ERROR_OUT_OF_CANVAS;
	}
	if ((s.y - dr_h) < 0 || (s.x - dr_w) < 0) {
		return ERROR_OUT_OF_CANVAS;
	}
	if (s.width % 2 == 0 || s.height % 2 == 0) {
		return ERROR_INVALID_INPUT;
	}

	int id = shapes_.size();
	shapes_.push_back(s);

	if (s.type == RECTANGLE) {

		for (int i = s.y - dr_h; i <= s.y + dr_h; i++) {
			for (int j = s.x - dr_w; j <= s.x + dr_w; j++) {
				stage_[i][j] = s.brush;
			}
		}
	}
	else if (s.type == TRIANGLE_UP) {


	}
	else if (s.type == TRIANGLE_DOWN) {

	}

	return id;
}

void Canvas::DeleteShape(int index)
{
	/*Implement here*/
	if (index >= 0 && index < shapes_.size()) {
		shapes_.erase(shapes_.begin() + index);
	}
}

void Canvas::Draw(ostream& os)
{
	/*Implement here*/


	cout << " ";
	for (int i = 0; i<stage_[0].length(); i++) {
		cout << i;
	}
	cout << endl;
	for (int i = 0; i < stage_.size(); i++) {
		cout << i;
		cout << stage_[i] << endl;
	}

}

void Canvas::Dump(ostream& os)
{
	/*Implement here*/

}
