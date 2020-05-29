#include <iostream>
#include <string>
#include<vector>
#include "reply_admin.h"

using namespace std;

bool replyOperation(ReplyAdmin *_replyAdmin)
{
	string inputs;
	getline(cin, inputs);

	if (inputs == "#quit") return false;
	else if (inputs.find("#remove") != string::npos)
	{
		if (inputs.find("-") != string::npos && inputs.find(",") == string::npos) {
			size_t pos = inputs.find("-");
			int st_num = stoi(inputs.substr(8, pos - 8));
			int ed_num = stoi(inputs.substr(pos + 1, inputs.length() - pos - 1));
			if (_replyAdmin->removeChat(st_num, ed_num)) {
				_replyAdmin->printChat();
			}

		}
		else if (inputs.find(",") != string::npos && inputs.find("-") == string::npos) {

			size_t found = inputs.find_first_of(",");
			vector<size_t> dot;
			vector<int> index;
			dot.push_back(found);

			while (found != string::npos) {
				found = inputs.find_first_of(",", found + 1);
				dot.push_back(found);

			}


			size_t first = 8;
			for (int i = 0; i < dot.size(); i++) {
				int rm = stoi(inputs.substr(first, dot[i] - first));
				index.push_back(rm);
				first = dot[i] + 1;
			}
			if (_replyAdmin->removeChat(index.begin(), index.size())) {
				_replyAdmin->printChat();
			}

		}
		else {
			string s = inputs.substr(8, inputs.length() - 8);
			bool chk = true;
			for (int i = 0; i < s.length(); i++) {
				if (isdigit(s[i]) == 0) {
					chk = false;
				}
			}

			if (chk) {
				int rm = stoi(s);

				if (_replyAdmin->removeChat(rm)) {
					_replyAdmin->printChat();
				}

			}

		}

	}
	else if (_replyAdmin->addChat(inputs)) _replyAdmin->printChat();

	return true;
}

int main(void)
{
	ReplyAdmin *replyAdmin = new ReplyAdmin();

	replyAdmin->addChat("Hello, Reply Administrator!");
	replyAdmin->addChat("I will be a good programmer.");
	replyAdmin->addChat("This class is awesome.");
	replyAdmin->addChat("Professor Lim is wise.");
	replyAdmin->addChat("Two TAs are kind and helpful.");
	replyAdmin->addChat("I think male TA looks cool.");

	while (replyOperation(replyAdmin)) {  }

	delete replyAdmin;
	return 0;
}
