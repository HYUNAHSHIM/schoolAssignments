#include <iostream>
#include "parse_radix.h"

int parse::ParseRadix(const string& number) {
	if (number.find("-") != string::npos) {
		string c;
		int sum = 0;
		c= number.substr(0, number.find("-"));
		radixn = stoi(number.substr(number.find("-") + 1, number.size() - number.find("-") - 1));
		for (int i = c.size(); i >=0; i--) {
			for (int j = 0; j < c.size()-i; j++) {
				sum += (c.at(i) - 48)*radixn;
			}
		}
		sum /= radixn;
		return sum;
	}
	else { return stoi(number); }
}

string parse::ConvertRadix(int number, int radix) {
	int result = 0;

	number *= radix;

	for (int count = 1; number /= radix; count *= 10) result += (number%radix)*count;

	return to_string(result);



}
