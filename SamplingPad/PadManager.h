#pragma once

#include "Track.h"
#include "Channel.h"
#define NULL 0

class PadManager {
public:

	static PadManager* getInstance() {
		if (instance == NULL)
			instance = new PadManager();

		return instance;
	}

	Track* getTrack() {
		return track;
	}

	bool isPlaying() { return playing; }
	void togglePlaying() { playing = !playing; }

	void setBpm(double bpm) { this->bpm = bpm; }
	double getBpm() { return bpm; }
	
	void setPlayedLength(double playedLength) { this->playedLength = playedLength; }
	double getPlayedLength() { return playedLength; }

	void setPlayBar(CStatic* playBar) { this->playBar = playBar; }
	CStatic* getPlayBar() { return playBar; }

private:
	PadManager() {
		track = new Track();
		playing = 0;
		playedLength = 0;
		bpm = 80;
	}
	static PadManager* instance;
	Track* track;
	bool playing;
	double bpm;
	double playedLength;
	CStatic* playBar;
};