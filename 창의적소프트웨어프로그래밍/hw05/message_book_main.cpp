#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "message_book.h"

using namespace std;

int main(void) {
	MessageBook messagebook;

	while (true) {
		string word;
		getline(cin, word);
		if (word.find("add") != string::npos) {
			size_t found = word.find_first_of("0123456789");
			size_t num_ed;
			size_t num_st = 4;
			while (found != string::npos) {
				found = word.find_first_of("0123456789", found + 1);
				if (found != string::npos) {
					num_ed = found;
				}
			}
			int key = stoi(word.substr(num_st, num_ed + 1 - num_st));
			string str = word.substr(num_ed + 2, word.size() - (num_ed + 2));
			messagebook.AddMessage(key, str);

		}
		else if (word.find("delete") != string::npos) {
			size_t found = word.find_first_of("0123456789");
			size_t num_ed;
			size_t num_st = 7;
			while (found != string::npos) {
				found = word.find_first_of("0123456789", found + 1);
				if (found != string::npos) {
					num_ed = found;
				}
			}

			int key = stoi(word.substr(num_st, num_ed + 1 - num_st));
			messagebook.DeleteMessage(key);

		}
		else if (word.find("print") != string::npos) {
			size_t found = word.find_first_of("0123456789");
			size_t num_ed;
			size_t num_st = 6;
			while (found != string::npos) {
				found = word.find_first_of("0123456789", found + 1);
				if (found != string::npos) {
					num_ed = found;
				}
			}

			int key = stoi(word.substr(num_st, num_ed + 1 - num_st));
			if (messagebook.FindMessage(key)) {
				cout << messagebook.GetMessage(key) << endl;
			}
		}
		else if (word.find("list") != string::npos) {
			messagebook.ListMessage();

		}
		else {
			break;
		}
	}
	return 0;
}
