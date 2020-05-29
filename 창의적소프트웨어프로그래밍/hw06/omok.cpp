#include "omok.h"
#include <iostream>
#include <vector>
#define max_v(a,b) ((a)>(b))?(a):(b)

using namespace std;

Omok::Omok() {
	/*Implement here*/
	blacks_turn_ = true;
	for (int i = 0; i<19; i++) {
		stage_.push_back("...................");
	}
	recentX_ = -1;
	recentY_ = -1;
}

bool Omok::Put(int x, int y) {
	/*Implement here*/

	if (x >= 0 && x <= 18 && y >= 0 && y <= 18) {
		if (stage_[y][x] == '.') {

			recentX_ = x;
			recentY_ = y;

			if (IsBlacksTurn()) {
				stage_[recentY_][recentX_] = 'o';
				blacks_turn_ = false;
			}
			else {
				stage_[recentY_][recentX_] = 'x';
				blacks_turn_ = true;
			}

			return true;

		}
		else {
			return false;
		}
	}
	return false;
}

bool Omok::IsOmok(bool* is_winner_black) const {
	int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
	int dy[8] = { 1, -1, 0, 0, 1, -1, 1, -1 };
	int x_direc;
	int y_direc;

	char dol;

	if (blacks_turn_) {
		dol = 'x';
	}
	else {
		dol = 'o';
	}
	int total_cnt = 0;
	if (recentY_ != -1 && recentX_ != -1) {
		for (int i = 0; i<8; i++) {
			int cnt = 0;

			int nx = recentX_ + dx[i];
			int ny = recentY_ + dy[i];
			if (nx < 0 || nx > 18 || ny <0 || ny > 18) {
				continue;
			}

			if (stage_[ny][nx] == dol) {
				x_direc = dx[i];
				y_direc = dy[i];

				int nny = ny + dy[i], nnx = nx + dx[i];

				if (nnx < 0 || nnx > 18 || nny <0 || nny > 18) {
					continue;
				}

				while (stage_[nny][nnx] == dol) {
					cnt += 1;
					nny += y_direc;
					nnx += x_direc;
					if (nnx < 0 || nnx > 18 || nny <0 || nny > 18) {
						break;
					}
				}

				nny = ny - dy[i], nnx = nx - dx[i];

				while (stage_[nny][nnx] == dol) {
					cnt += 1;
					nny -= y_direc;
					nnx -= x_direc;
					if (nnx < 0 || nnx > 18 || nny <0 || nny > 18) {
						break;
					}
				}

			}

			total_cnt = max_v(total_cnt, cnt);
		}
		if (total_cnt + 1 == 5) {
			if (dol == 'o') {
				*is_winner_black = true;
			}
			else if (dol == 'x') {
				*is_winner_black = false;
			}
			return true;
		}
	}

	return false;
}
ostream& operator<<(std::ostream& os, const Omok& omok) {
	/*Implement here*/
	for (int i = 0; i<19; i++) {
		for (int j = 0; j < 19; j++) {
			os << omok.stage_[i][j];
			if (j <= 17) {
				os << " ";
			}
		}
		os << endl;
	}
	return os;
}
