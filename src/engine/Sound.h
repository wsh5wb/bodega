#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

class Sound{

public:
	Sound();
	~Sound();

	void playSFX();
	void playMusic();
	void loadMusic(const char* filepath);
	void loadSFX(const char* filepath);
	void stopMusic();

private:
	Mix_Chunk *wave;
	Mix_Music *music;
	/*SDL_AudioSpec wavSpec, wavHave;
	Uint32  wavLength;
	Uint8 *wavBuffer;
	SDL_AudioDeviceID deviceId;*/

};

#endif
