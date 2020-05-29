
#include "new_vector.h"
#include <sstream>

using namespace std;

//template <typename T>


void NewVector::addTo(int _value)
{
	/* Implement here*/
	intMap_.insert(make_pair(count_, _value));
}

void NewVector::addTo(double _value)
{
	/* Implement here*/
	doubleMap_.insert(make_pair(count_, _value));
}

void NewVector::addTo(char _value)
{
	/* Implement here*/
	charMap_.insert(make_pair(count_, _value));
}

template <typename T>
string NumberToString(T Number)
{
	/* Implement here*/

}

ostream& operator << (ostream& _os, const NewVector _nv)
{
	/* Implement here*/
	const int cnt = _nv.count();
	for (int i = 0; i < cnt; i++) {
		if (_nv.intMap_.find(i) != _nv.intMap_.end()) {
			_os << _nv.intMap_.at(i);
		}
		else if (_nv.doubleMap_.find(i) != _nv.doubleMap_.end()) {
			_os << _nv.doubleMap_.at(i);
		}
		else if (_nv.charMap_.find(i) != _nv.charMap_.end()) {
			_os << _nv.charMap_.at(i);
		}

		if (i < cnt - 1) {
			_os << " ";
		}
	}

	_os << endl;
	return _os;

}