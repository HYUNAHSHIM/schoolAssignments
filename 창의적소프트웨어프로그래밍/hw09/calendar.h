#ifndef __CALENDAR_H__
#define __CALENDAR_H__

#include <string>
#include <iostream>

using namespace std;

class Date {
public:
	Date(int year = 0, int month = 0, int day = 0);
	void NextDay(int n = 1);
	bool SetDate(int year, int month, int day);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

private:
	static int GetDaysInYear(int year);

private:
	int year_;
	int month_;
	int day_;
};

class MyDateException {
public:
	MyDateException(const string& msg);
	~MyDateException() {}
	virtual string GetMessage() { return 0; };
protected:
	string input_date; 
};

class InvalidDateException : public MyDateException {
public:
	InvalidDateException(const string& str) : MyDateException(str) {}
	virtual string GetMessage();
};

class InvalidDateFormatException : public MyDateException {
public:
	InvalidDateFormatException(const string& str) : MyDateException(str) {}
	virtual string GetMessage();
};

ostream& operator<<(ostream& os, const Date& c);
istream& operator>>(istream& is, Date& c);

#endif
