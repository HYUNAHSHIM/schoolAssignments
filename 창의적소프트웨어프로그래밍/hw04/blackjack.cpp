#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	while (true) {
		vector<char> card;
		string cards="\0";
		int num = 0;
		int sum = 0;
		bool ifA = false;
		card.clear();
		getline(cin, cards);
		num = cards[0] - 48;

		char*cardP = new char[num * 2 - 1];

		for (int i = 2; i < num * 2 + 1; i++) {
			cardP[i - 2] = cards[i];
		}

		for (int i = 0; i < num * 2 - 1; i++) {
			if (i % 2 == 0) {
				card.push_back(cardP[i]);
			}
		}

		for (int i = 0; i < num; i++) {
			if (isdigit(card[i]) != 0) {
				sum += (card[i] - 48);
			}
			else if (card[i] == 'J' || card[i] == 'Q' || card[i] == 'K') {
				sum += 10;
			}
			else if (card[i] == 'A') {
				ifA = true;
			}
			else {
				return 0;
			}
		}
		if (ifA == true) {

			if (10 - sum < 0 && 20 - sum > 0) {
				sum += 1;
			}
			else if (10 - sum >= 0 && 20 - sum > 0) {
				sum += 11;
			}
		}

		if (sum > 21) {
			cout << "Exeed" << endl;
		}
		else if (sum == 21) {
			cout << "BlackJack" << endl;
		}
		else {
			cout << sum << endl;
		}

		delete[] cardP;
	}
}
