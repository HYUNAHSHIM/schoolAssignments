#include "calendar.h"
#include <vector>
#include <cstdlib>

enum months {
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

const int common_month_date[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}

void Date::NextDay(int n) {
	int days = 0;
	for (int i = 1; i < month_; i++) {
		days += common_month_date[i];
		if (i == 2) {
			days += GetDaysInYear(year_) - 365;
		}
	}
	days += day_;
	days += n;
	while (days <= 0) {
		year_--;
		days += GetDaysInYear(year_);
	}
	while (days > GetDaysInYear(year_)) {
		days -= GetDaysInYear(year_);
		year_++;
	}
	month_ = 1;
	while (days > common_month_date[month_]) {
		if (month_ == 2 && GetDaysInYear(year_) == 366) {
			if (days == 29) {
				break;
			}
			else {
				days -= 29;
			}
		}
		else {
			days -= common_month_date[month_];
		}
		month_++;
	}
	day_ = days;
}

bool Date::SetDate(int year, int month, int day) {
	if (month < 1 || month > 12) {
		return false;
	}
	else if (day < 0 || day > common_month_date[month]) {
		if (month == 2) {
			if (GetDaysInYear(year) != 366 || day != 29) {
				return false;
			}
		}
		else {
			return false;
		}
	}
	year_ = year;
	month_ = month;
	day_ = day;
	return true;
}

int Date::GetYear() const {
	return year_;
}

int Date::GetMonth() const {
	return month_;
}

int Date::GetDay() const {
	return day_;
}

int Date::GetDaysInYear(int year) {
	if (year % 400 == 0) {
		return 366;
	}
	else if (year % 100 == 0) {
		return 365;
	}
	else if (year % 4 == 0) {
		return 366;
	}
	else {
		return 365;
	}
	return 0;
}

ostream& operator<<(ostream& os, const Date& date) {
	os << date.GetYear() << '.' << date.GetMonth() <<
		'.' << date.GetDay() << endl;
	return os;
}

istream& operator>>(istream& is, Date& c) {
	string input_string;
	is >> input_string;
	int cnt = 0;
	for (int i = 0; i < input_string.length(); i++) {
		if (input_string[i] == '.') {
			cnt++;
		}
		else if (((int)input_string[i] < (int)'0' || (int)input_string[i] > (int)'9') && input_string[i] != '-') {
			cnt = -1;
			break;
		}
	}
	if (cnt != 2) {
		InvalidDateFormatException* ex = new InvalidDateFormatException(input_string);
		throw ex;
	}
	string tmp;
	tmp = input_string;
	int year = stoi(tmp.substr(0, tmp.find('.')));
	tmp = tmp.substr(tmp.find('.') + 1, tmp.length());
	int month = stoi(tmp.substr(0, tmp.find('.')));
	tmp = tmp.substr(tmp.find('.') + 1, tmp.length());
	int day = stoi(tmp);

	if (!c.SetDate(year, month, day)) {
		InvalidDateException* ex = new InvalidDateException(input_string);
		throw ex;
	}

	return is;
}

MyDateException::MyDateException(const string& msg) {
	input_date = msg;
}

string InvalidDateException::GetMessage() {
	string res;
	res = "Invalid date: ";
	res += input_date;
	return res;
}

string InvalidDateFormatException::GetMessage() {
	string res;
	res = "InvalidDateFormatException expected: YYYY.MM.DD but was ";
	res += input_date;
	return res;
}
