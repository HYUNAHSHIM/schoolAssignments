// skeleton code


#include <iostream>
#include "new_vector.h"
using namespace std;

int main(void)
{
	NewVector nv = NewVector();
	while (true)
	{
		string type;
		cin >> type;

		if (type == "i")
		{
			int value;
			cin >> value;
			nv.add(value);
		}
		else if (type == "d")
		{
			double value;
			cin >> value;
			nv.add(value);
		}
		else if (type == "c")
		{
			char value;
			cin >> value;
			nv.add(value);
		}
		else if (type == "print") cout << nv;
		else if (type == "q") break;
	}
	return 0;
}
