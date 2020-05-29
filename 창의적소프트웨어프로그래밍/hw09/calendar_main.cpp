#include "calendar.h"

int main() {
	string cmd;
	Date date;
	int num;
	do {
		cin >> cmd;

		if (cmd == "set") {
			try {
				cin >> date;
			}
			catch (MyDateException *e) {
				cout << e->GetMessage() << endl;
				delete e;
				continue;
			}
			cout << date;
		}
		else if (cmd == "next_day") {
			if (date.GetDay() == 0) {
				continue;
			}
			date.NextDay();
			cout << date;
		}
		else if (cmd == "next") {
			cin >> num;
			if (date.GetDay() == 0) {
				continue;
			}
			date.NextDay(num);
			cout << date;
		}
	} while (cmd != "quit");

	return 0;
}
