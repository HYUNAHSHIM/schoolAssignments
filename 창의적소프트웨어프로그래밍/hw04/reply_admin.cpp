#include "reply_admin.h"
#include<algorithm>

ReplyAdmin::ReplyAdmin() {
}

ReplyAdmin::~ReplyAdmin() {
	
}

bool ReplyAdmin::addChat(string _chat) {
	chats.push_back(_chat);
	return true;
}

bool ReplyAdmin::removeChat(int _index) {
	
	if (_index >= 0 && _index <= chats.size() - 1) {

		
		return true;
	}
	return false;
}

bool ReplyAdmin::removeChat(vector<int>::iterator _it, int _count) {
	sort(_it, _it + _count);
	int cnt = chats.size();
	for (int i = _count - 1; i >= 0; i--) {
		int id = *(_it + i);
		std::list<string>::iterator it2;

		if (id >= 0 && id <= chats.size() - 1) {

			it2 = chats.begin();
			advance(it2, id);

			chats.erase(it2);
		}
	}
	if (chats.size() == cnt)
		return false;

	return true;
}

bool ReplyAdmin::removeChat(int _start, int _end) {
	std::list<string>::iterator it1, it2;

	it1 = chats.begin();
	it2 = chats.begin();
	advance(it1, _start);
	advance(it2, _end + 1);
	if (_start >= 0 && _start <= chats.size() - 1 && _end >= 0 && _end <= chats.size()) {
		chats.erase(it1, it2);
		return true;
	}
	else if (_start >= 0 && _start <= chats.size() - 1 && _end >= chats.size()) {
		chats.erase(it1, chats.end());
		return true;
	}
	return false;
}

void ReplyAdmin::printChat() {
	int count = chats.size();
	list<string>::iterator it = chats.begin();
	for (int i = 0; i<count; ++i)
	{
		cout << i << " " << *it << endl;
		if (it != chats.end()) {
			it++;
		}
	}
}
