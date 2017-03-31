#pragma once

#include "Channel.h"

class Track {
public:
	// constructor
	Track() {
		length = 8; // 8분음표 8개
		slice = 1; // 각 칸은 1개로 분할

		cnlSize = 4; // 타악기 4개
		cnls = new Channel[cnlSize];
		for (int i = 0; i < cnlSize; i++)
			cnls[i].setSize(length, slice);
	}

	// getter
	int getLength() { return length; }
	int getSlice() { return slice; }
	int getChannelSize() { return cnlSize; }
	Channel* getChannelPtr() { return cnls; }

	// setter
	void setLength(int _length) {
		length = _length;
		for (int i = 0; i < cnlSize; i++)
			cnls[i].setSize(length, slice);
	}

	void setSlice(int _slice) {
		int gcd = myGCD(slice, _slice);

		for (int i = 0; i < cnlSize; i++) {
			cnls[i].scaleDown(slice / gcd);
			cnls[i].scaleUp(_slice / gcd);
		}

		slice = _slice;
	}

	// destructor
	~Track() {
		delete[] cnls;
	}
private:
	int length; // 4, 8, 12, 16
	int slice; // 1,2,3
	
	int cnlSize; // 1이상
	Channel* cnls;

	int myGCD(int x, int y) {
		if (x % y == 0)
			return y;
		if (y % x == 0)
			return x;

		if (x == y)
			return x;
		else if (x > y)
			return myGCD(x % y, y);
		else
			return myGCD(x, y % x);
	}
};