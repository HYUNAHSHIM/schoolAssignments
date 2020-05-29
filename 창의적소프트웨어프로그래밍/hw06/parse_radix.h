#ifndef __hw06__parse_radix__
#define __hw06__parse_radix__

#include <iostream>
#include <string>

using namespace std;

class parse {
	int num;//n진법의 숫자
	int radixn;//n진법
	int radix10;//10진법으로 바꿈!

public:
	int ParseRadix(const string& number);
	string ConvertRadix(int number, int radix);
	};


#endif