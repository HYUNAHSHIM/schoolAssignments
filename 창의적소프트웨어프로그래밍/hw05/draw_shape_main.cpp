#include <iostream>
#include <string>
#include "draw_shape.h"


using namespace std;

int main()
{
	int row, col;

	cin >> row >> col;

	Canvas canvas(row, col);

	canvas.Draw(cout);

	while (true)
	{
		string word;

		cin >> word;

		if (word == "add")
		{
			cin >> word;

			if (word == "rect")
			{
				/*Implement here*/
				int x, y, w, h;
				char brush;
				cin >> x >> y >> w >> h >> brush;
				Shape sh;
				Shape& s = sh;
				s.type = RECTANGLE;
					s.x = x;
				s.y = y;
				s.width = w;
				s.height = h;
				s.brush = brush;
				int chk = canvas.AddShape(s);
				if (chk == -1) {
					cout << "error out of canvas" << endl;
				}
				else if (chk == -2) {
					cout << "error invalid input" << endl;
				}

			}

			else if (word == "tri_up")
			{
				
				Shape sh;
				Shape& s = sh;
				s.type = TRIANGLE_UP;
			}

			else if (word == "tri_down")
			{
				
				Shape sh;
				Shape& s = sh;
				s.type = TRIANGLE_DOWN;
			}

			else
				break;
		}

		else if (word == "delete")
		{
		}

		else if (word == "draw")
		{
			canvas.Draw(cout);
		}
		else if (word == "dump")
		{
		}

		else
			break;
	}
}
