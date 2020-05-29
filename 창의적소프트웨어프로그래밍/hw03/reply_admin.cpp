#inlude <iostream>
#include "reply_admin.h"

using namespace std;

int ReplyAdmin::getChatCount() {
	 int i;
     for (i = 0; i < NUM_OF_CHAT; ++i) {
     string s = chats[i];
     if (s.empty() == true) break;
     }
     return i;
}

ReplyAdmin::ReplyAdmin() {
	 chats = new string[NUM_OF_CHAT];

	 addChat("Hello, Reply Administrator!");
	 addChat("I will be a good programmer.");
	 addChat("This class is awesome.");
     addChat("Professor Lim is wise.");
	 addChat("Two TAs are kind and helpful.");
	 addChat("I think male TA looks cool.");

}//chats를 NUM_OF_CHAT만큼 초기화

ReplyAdmin::~ReplyAdmin() {
	 delete[] chats;
}//chats를 delete

bool ReplyAdmin::addChat(string _chat) {
	 int i = 0;
	 while (chats[i] != "") {
	    i++;
	 }
	 if (i > NUM_OF_CHAT) return false;
	 chats[i] = _chat;

	 return true;

}//_chat 을 chats에 추가(추가 실패시 false리턴)

bool ReplyAdmin::removeChat(int _index) {
	 int i = 0;
	 if (chats[_index] == "") return false;
	 else {
	     chats[_index] ="";
	     for (i = _index + 1; chats[i] != ""; i++) {
		      chats[i - 1] = chats[i];
	     }//앞으로 땡김
	     chats[i - 1] = "";
	  }
	 return true;
}// #remove #

bool ReplyAdmin::removeChat(int *_indices, int _count) {
	 int j = 0;
	 int num = _count;
	 for (int i = 0; i < _count; i++) {
	     chats[_indices[i]] = "";
	  }
	 for (int i = _indices[num-1]; num > 0; num--) {
	     for (j = i + 1; chats[j] != ""; j++) {
		     chats[j - 1] = chats[j];
	     }
	  }//앞으로 땡김
	 for (int i = j- _count; i <= j - 1; i++) {
		   chats[i] = "";
	  }
	 return true;
}// #remove #,#,#,#

bool ReplyAdmin::removeChat(int _start, int _end) {
	 int j = 0;
     for (int i = _start; i <= _end; i++) {
	    chats[i] = "";
	 }
     for (int i = _end + 1; chats[_end+j+1] != "";j++) {
	     chats[_start + j] = chats[_end + j + 1];
     }
     for (int i = j + _start; i < _end + j + 1; i++) {
         chats[i] = "";
	 }
	 return true;
}// #remove #-#

void ReplyAdmin::printChat() {
	 int count = getChatCount();
	 for (int i = 0; i<count; ++i) {
	    cout << i << " " << chats[i] << endl;
	 }
} 

