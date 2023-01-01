#pragma once

#include <audiere.h>

using namespace audiere;

class Sound
{
private:
	OutputStreamPtr sound;
public:
	Sound(AudioDevicePtr aud_dev, char* filename, float volume);
	~Sound(void);
	void play(bool repeat);
	void play(bool _reset, bool repeat);
	void stop();
	void reset();
	void stopnreset();
	void setvolume(float volume);
	bool getisplaying();
};

