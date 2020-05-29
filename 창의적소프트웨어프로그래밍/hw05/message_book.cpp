#include <iostream>
#include <string>
#include <map>
#include "message_book.h"

MessageBook::MessageBook() {
}

MessageBook::~MessageBook() {
}

void MessageBook::AddMessage(int number, const string& message) {
	messages_[number] = message;
}

void MessageBook::DeleteMessage(int number) {
	messages_.erase(number);
}

const string MessageBook::GetMessage(int number) const {
	string str;
	str = messages_.find(number)->second;
	return str;
}

bool MessageBook::FindMessage(int number) {
	map<int, string>::iterator it;
	it = messages_.find(number);
	if (it != messages_.end())
		return true;
	return false;
}
void MessageBook::ListMessage() {
	map<int, string>::iterator it;

	for (it = messages_.begin(); it != messages_.end(); it++) {
		cout << it->first << ": " << it->second << endl;
	}

}
