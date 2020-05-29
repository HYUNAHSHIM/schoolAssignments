#ifndef _SORTED_ARRAY_H_
#define _SORTED_ARRAY_H_
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <typeinfo>
using namespace std;

template <typename T>
class SortedArray
{
public:
	SortedArray()
	{
		values_ = NULL;

		size_ = 0;

		alloc_ = 0;
	}

	SortedArray(const SortedArray& a)
	{
		values_ = a.values_;

		size_ = a.size_;

		alloc_ = a.alloc_;
	}

	SortedArray(size_t size)
	{
		values_ = NULL;

		size_ = size;

		alloc_ = 0;
	}

	~SortedArray()
	{
	}


	SortedArray& operator=(SortedArray& a)
	{

		return a;
	}

	size_t size() const
	{
		return size_;
	}

	const T& operator()(int idx) const
	{
		return values_[idx];
	}

	void Reserve(int size)
	{
		/* Implement here*/
		alloc_ = size;
		values_ = new T[alloc_];
		// 메모리 할당
	}


	void Add(const T& value)
	{
		/* Implement here*/
		if (size_<alloc_) {
			values_[size_] = value;
			size_++;
		}

		if (size_ == alloc_) {
			sort(values_, values_ + alloc_);
		}

	}

	int Find(const T& value)
	{
		/* Implement here*/
		int l = 0;
		int r = alloc_ - 1;
		while (l <= r) {
			int mid = (r + l) / 2;

			if (values_[mid] == value) {
				return mid;
			}
			else if (values_[mid] > value) {
				r = mid - 1;
			}
			else if (values_[mid] < value) {
				l = mid + 1;
			}
		}
		return -1;
	}

private:
	T* values_;
	int size_, alloc_;

};

template <typename T>
istream& operator>>(istream& is, SortedArray<T>& a)
{
	/* Implement here*/
	size_t alloc;
	cin >> alloc;
	a.Reserve(alloc);
	T* array = new T[alloc];

	for (int i = 0; i < alloc; i++) {
		cin >> array[i];
		const T& val = array[i];
		a.Add(val);

	}
	//a.Add(value);
	//add 를 이용해 값을 넣자.
	return is;
}

template <typename T>
ostream& operator<<(ostream& os, const SortedArray<T>& a)
{
	for (int i = 0; i<a.size(); i++) {
		os << a(i);
		if (i < a.size() - 1) {
			os << " ";
		}
	}
	return os;

}

#endif
