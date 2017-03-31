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

private:
	PadManager() {
		track = new Track();
	}
	static PadManager* instance;
	Track* track;
};