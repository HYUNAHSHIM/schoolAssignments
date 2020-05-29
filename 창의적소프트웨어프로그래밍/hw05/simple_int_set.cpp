
#include "simple_int_set.h"

#include <iostream>
#include <vector>

using namespace std;

SimpleIntSet::SimpleIntSet() {
	/* TODO: Implement here. */
}

SimpleIntSet::~SimpleIntSet() {
	/* TODO: Implement here. */
	elements_.clear();
}
void SimpleIntSet::set_clear() {
	elements_.clear();
}

void SimpleIntSet::Initialize(string text) {
	/* TODO: Implement here. */
	vector<int> space;
	// space의 위치를 기억할 벡터
	size_t found = text.find_first_of(" ");
	while (found != string::npos) {
		found = text.find_first_of(" ", found + 1);
		space.push_back(found);
	}

	space.erase(space.end() - 1);

	size_t first = 2;

	// 중복 체크해줄 변수
	for (int i = 0; i<space.size(); i++) {
		string number = text.substr(first, space[i] - first);
		first = space[i] + 1;

		elements_.insert(stoi(number));
		// 다시 false 값으로 초기화 해줌.
	}
}

void SimpleIntSet::Print() {
	/* TODO: Modify here. */
	cout << "{";
	set<int>::iterator it;
	for (it = elements_.begin(); it != elements_.end(); it++) {
		cout << " " << *it;
	}

	cout << " }" << endl;
}


void SimpleIntSet::operator=(const SimpleIntSet& si) {
	elements_ = si.elements_;
}

SimpleIntSet SimpleIntSet::operator+(const SimpleIntSet& si) {
	SimpleIntSet tmp;
	set<int>::iterator it;
	for (it = elements_.begin(); it != elements_.end(); it++) {
		tmp.elements_.insert(*it);
	}
	for (it = si.elements_.begin(); it != si.elements_.end(); it++) {
		tmp.elements_.insert(*it);
	}
	return tmp;
}
SimpleIntSet SimpleIntSet::operator-(const SimpleIntSet& si) {
	SimpleIntSet tmp;
	set<int>::iterator it;
	for (it = elements_.begin(); it != elements_.end(); it++) {
		if (si.elements_.find(*it) == si.elements_.end()) {
			tmp.elements_.insert(*it);
		}
	}
	return tmp;
}
SimpleIntSet SimpleIntSet::operator*(const SimpleIntSet& si) {
	SimpleIntSet tmp;
	set<int>::iterator it;
	for (it = elements_.begin(); it != elements_.end(); it++) {
		if (si.elements_.find(*it) != si.elements_.end()) {
			tmp.elements_.insert(*it);
		}
	}

	return tmp;
}

