#include <iostream>
#include <string>
#include "parse_radix.h"

using namespace std;

int main() {
	while (true) {
		string str="\0";
		getline(cin, str);

		if (str.find("quit") != string::npos) {
			return 0;
		}
		else if (str.find("eval") != string::npos) {
			str.erase(0, 4);
			parse num1;
			parse num2;
			parse num3;
			if (str.find("+") != string::npos) {
				int a = num1.ParseRadix(str.substr(0, str.find("+") - 2));
				str.erase(0, str.find("+") + 1);
				int b = num2.ParseRadix(str.substr(0, str.find(" ")-1));
				int radix = stoi(str.substr(str.find(" ") + 1, str.size()-str.find(" ")));//문자열을 숫자로
				cout << num3.ConvertRadix(a + b, radix) << endl;
			}
			else if (str.find("-") != string::npos) {
				int a = num1.ParseRadix(str.substr(0, str.find("-") - 2));
				str.erase(0, str.find("-") + 1);
				int b = num2.ParseRadix(str.substr(0, str.find(" ")-1));
				int radix = stoi(str.substr(str.find(" ") + 1, str.size()-str.find(" ")));//문자열을 숫자로
				cout << num3.ConvertRadix(a - b, radix) << endl;
			}
			else if (str.find("*") != string::npos) {
				int a = num1.ParseRadix(str.substr(0, str.find("*") - 2));
				str.erase(0, str.find("*") + 1);
				int b = num2.ParseRadix(str.substr(0, str.find(" ")-1));
				int radix = stoi(str.substr(str.find(" ") + 1, str.size() - str.find(" ")));//문자열을 숫자로
				cout << num3.ConvertRadix(a * b, radix) << endl;
			}
			else if (str.find("/") != string::npos) {
				int a = num1.ParseRadix(str.substr(0, str.find("/") - 2));
				str.erase(0, str.find("/") + 1);
				int b = num2.ParseRadix(str.substr(0, str.find(" ")-1));
				int radix = stoi(str.substr(str.find(" ") + 1, str.size() - str.find(" ")));//문자열을 숫자로
				cout << num3.ConvertRadix(a / b, radix) << endl;
			}
			else if (str.find(">") != string::npos) {
				int a = num1.ParseRadix(str.substr(0, str.find(">") - 2));
				str.erase(0, str.find(">") + 1);
				int b = num2.ParseRadix(str.substr(0, str.size()));
				if (a > b) {
					cout << "true" << endl;
				}
				else { cout << "false" << endl; }
				
			}
			else if (str.find("<") != string::npos) {
				int a = num1.ParseRadix(str.substr(0, str.find("<") - 2));
				str.erase(0, str.find("<") + 1);
				int b = num2.ParseRadix(str.substr(0, str.size()));
				if (a < b) {
					cout << "true" << endl;
				}
				else { cout << "false" << endl; }

			}
			else if (str.find("==") != string::npos) {
				int a = num1.ParseRadix(str.substr(0, str.find("==") - 2));
				str.erase(0, str.find("==") + 2);
				int b = num2.ParseRadix(str.substr(0, str.size()));
				if (a == b) {
					cout << "true" << endl;
				}
				else { cout << "false" << endl; }

			}
		}
	}
}