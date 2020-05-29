#ifndef _DRAW_SHAPE_H_
#define _DRAW_SHAPE_H_
#include <vector>

using namespace std;

enum {RECTANGLE, TRIANGLE_UP, TRIANGLE_DOWN};

enum {ERROR_OUT_OF_CANVAS=-1, ERROR_INVALID_INPUT=-2};

struct Shape
{
	string type;

	int x, y;

	int width, height;

	char brush;
};

class Canvas
{
	public:
		Canvas(size_t row, size_t col);

		~Canvas();

		void AddShape(const Shape &s);

		void DeleteShape(int index);

		void Draw(ostream& os);
		
		void Dump(ostream& os);

		void Paper(char** s, int row, int col);

	private:
		size_t width_, height_; 

		vector<Shape> shapes_;
		vector<string> canvas_;
		vector<string>::iterator it;
		vector<Shape>::iterator its;
};

#endif
