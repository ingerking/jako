#include "sound.h"


Sound::Sound(AudioDevicePtr aud_dev, char* filename, float volume)
{
	sound=NULL;

	sound=OpenSound(aud_dev, filename, false);
	sound->setVolume(volume);
}


Sound::~Sound(void)
{
	stop();
	reset();
}

void Sound::play(bool repeat){
	if(!sound->isPlaying()){
		sound->setRepeat(repeat);
		sound->play();
	}
}

void Sound::play(bool _reset, bool repeat){
	if(_reset){
		if(sound->isPlaying()){
			sound->stop();
			sound->reset();
		}
		sound->setRepeat(repeat);
		sound->play();
	}
	else{
		if(!sound->isPlaying()){
			sound->setRepeat(repeat);
			sound->play();
		}
	}
}

void Sound::stop(){
	sound->stop();
}

void Sound::reset(){
	sound->reset();
}

void Sound::stopnreset(){
	if(sound->isPlaying()){
		sound->stop();
	}
	sound->reset();
}

void Sound::setvolume(float volume){
	sound->setVolume(volume);
}

bool Sound::getisplaying(){
	return sound->isPlaying();
}