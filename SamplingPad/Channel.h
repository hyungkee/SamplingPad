#pragma once

#define NULL 0

#ifndef min
#define min(x,y) ((x)<(y)?(x):(y))
#endif

class Channel {
public:
	// constructor
	Channel() : size(0), note(NULL) {}
	Channel(int _size) : size(_size), note(new int[_size]) { init();  }


	// getter
	const int getSize() { return size; }
	const int* getNotePtr() { return note; }
	const bool getMute() { return mute; }

	// setter
	void setSize(int _size) {  // ���� ��Ʈ���� �� ä���� �Ǿտ� ����
		int* past = note;
		note = new int[_size];
		for (int i = 0; i < min(size, _size); i++)	note[i] = past[i];
		delete[] past;
		size = _size;
	}
	void setSize(int _length, int _slice) { setSize(_length * _slice);  }
	void scaleUp(int _scale) { // ���� ��Ʈ���� �� ä�ο� ������ ��ġ
		int* past = note;
		note = new int[size * _scale];
		for (int i = 0; i < size; i++)	note[i * _scale] = past[i];
		delete[] past;
		size = size * _scale;
	}
	void scaleDown(int _scale) {
		int* past = note;
		note = new int[size / _scale];
		for (int i = 0; i < size / _scale; i++)	note[i] = past[i * _scale];
		delete[] past;
		size = size / _scale;
	}
	void toggle(int _pos) { note[_pos] = 1 - note[_pos]; } // note���� 0, 1�� �ִٰ� ����
	void setMute(bool _mute) { mute = _mute; }

	// method
	void init() {
		for (int i = 0; i < size; i++)	note[i] = 0;
	}

	// destructor
	~Channel() { delete[] note; }

private:
	int size;
	int* note;
	bool mute;
};