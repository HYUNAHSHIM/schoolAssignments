#ifndef _OMOK_H_
#define _OMOK_H_

#include <iostream>
#include <vector>

class Omok {
public:
	Omok();
	~Omok() { stage_.clear(); }

	bool Put(int x, int y);
	bool IsOmok(bool* is_winner_black) const;
	bool IsBlacksTurn() const { return blacks_turn_; }

	friend std::ostream& operator<<(std::ostream& os, const Omok& omok);

private:
	int width_, height_;
	int recentX_, recentY_;
	bool blacks_turn_;  
	std::vector<std::string> stage_;
};

std::ostream& operator<<(std::ostream& os, const Omok& omok);

#endif
