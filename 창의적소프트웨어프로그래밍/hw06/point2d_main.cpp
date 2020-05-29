#include <iostream>
#include "point2d.h"
#include <string>

using namespace std;

int main() {
	class Point p[10];
	class Point number;
	class Point number2;

	char c[10];
	int num = 0; 

	while (true) {
		string str = "\0";
		getline(cin, str);

		if (str.find("quit") != string::npos) {
			return 0;
		}
		else if (str.find("set") != string::npos) {
			bool exit = false;
			for (int i = 0; i < 10; i++) {
				if (c[i] == str.at(4)) {
					int a = str.at(6)-48;
					int b = str.at(8)-48;
					p[i].point2(a, b);
					exit = true;
				}
			}
			if (exit == false) {
				c[num] = str.at(4);
				int a = str.at(6) - 48;
				int b = str.at(8)- 48;
				p[num].point2(a, b);
				num++;
			}
		}

		else if (str.find("eval") != string::npos) {
			char first = str.at(5);
			char second = str.at(9);
			char oper = str.at(7);

			if (isdigit(first) != 0 && isdigit(second)==0) {
				number.point2(first - 48, first - 48);
				bool exit2 = false;
				for (int i = 0; i < 10; i++) {
					if (c[i] == second) {
						if (oper == '+') {
							(number + p[i]).point(number + p[i]);
						}
						else if (oper == '-'){
							(number - p[i]).point(number - p[i]);
						}
						else if (oper == '*') {
							(number * p[i]).point(number * p[i]);
						}
						exit2 = true;
					}
				}
				if (exit2 == false) {
						cout << "input error" << endl;
				}
			}
			else if (isdigit(first) == 0 && isdigit(second) != 0) {
				number2.point2(second - 48, second - 48);
				bool exit3 = false;
				for (int i = 0; i < 10; i++) {
					if (c[i] == first) {
						
						if (oper == '+') {
							(p[i] + number2).point(p[i] + number2);
						}
						else if (oper == '-') {
							(p[i] - number2).point(p[i] - number2);
						}
						else if (oper == '*') {
							(p[i] * number2).point(p[i] * number2);
						}
						exit3 = true;
					}
					
					}if (exit3 == false) {
						cout << "input error" << endl;
				}
			}
			else if (isdigit(first) == 0 && isdigit(second) == 0) {
				for (int i = 0; i < 10; i++) {
					if (c[i] == first) {
						bool exit4 = false;
						for (int j = 0; j < 10; j++) {
							
							if (c[j] == second) {
								if (oper == '+') {
									(p[i] + p[j]).point(p[i] + p[j]);
								}
								else if (oper == '-') {
									(p[i] - p[j]).point(p[i] - p[j]);
								}
								else if (oper == '*') {
									(p[i] * p[j]).point(p[i] * p[j]);
								}
								exit4 = true;
							}
							
								}if (exit4 == false) {
								cout << "input error" << endl;
						}
					}
				}
			}
			else if (isdigit(first) != 0 && isdigit(second) != 0) {
				number.point2(first - 48, first - 48);
				number2.point2(second - 48, second - 48);
				
				if (oper == '+') {
					(number+number2).point(number + number2);
				}
				else if (oper == '-') {
					(number - number2).point(number - number2);
				}
				else if (oper == '*') {
					(number * number2).point(number * number2);
				}
			}
		}
	}
}