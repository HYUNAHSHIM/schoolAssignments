#ifndef __SIMPLE_INT_SET__
#define __SIMPLE_INT_SET__

#include <string>
#include <set>

class SimpleIntSet {
public:
	SimpleIntSet();
	~SimpleIntSet();
	void Initialize(std::string text);
	void Print();
	void Sort(); // you can reuse your previous sort assignment
	void operator=(const SimpleIntSet& si);
	SimpleIntSet operator+(const SimpleIntSet& si);
	SimpleIntSet operator-(const SimpleIntSet& si);
	SimpleIntSet operator*(const SimpleIntSet& si);
	void set_clear();

	/* Implement operator overloading here */

private:
	std::set<int> elements_;

};

#endif
