#ifndef __hw06__parse_radix__
#define __hw06__parse_radix__

#include <iostream>
#include <string>

using namespace std;

class parse {
	int num;//n������ ����
	int radixn;//n����
	int radix10;//10�������� �ٲ�!

public:
	int ParseRadix(const string& number);
	string ConvertRadix(int number, int radix);
	};


#endif