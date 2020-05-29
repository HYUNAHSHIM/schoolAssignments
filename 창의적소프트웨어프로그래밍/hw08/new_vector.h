
#ifndef new_vector_h
#define new_vector_h

#include <map>
#include <iostream>
using namespace std;

class NewVector
{
public:
	NewVector() { count_ = 0; }
	template <typename T> void add(T _value)
	{
		addTo(_value);
		++count_;
	}
	inline int count()const { return count_; }

	friend ostream& operator << (ostream& _os, const NewVector _nv);

private:
	int count_;

	map<int, int> intMap_;
	map<int, double> doubleMap_;
	map<int, char> charMap_;

	void addTo(int _value);
	void addTo(double _value);
	void addTo(char _value);
};

#endif
