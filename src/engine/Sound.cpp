#include "Sound.h"

Sound::Sound(){
}

Sound::~Sound(){
      Mix_FreeChunk(wave);
      wave = NULL;
      Mix_FreeMusic(music);
      music = NULL;
}

void Sound::loadMusic(const char * filepath){
      this->music = Mix_LoadMUS(filepath);
}

void Sound::playMusic(){
    if( Mix_PlayingMusic() == 0 )
     {
         //Play the music
         Mix_PlayMusic(music, -1 );
     }
     //If music is being played
     else
     {
         //If the music is paused
         if( Mix_PausedMusic() == 1 )
         {
             //Resume the music
             Mix_ResumeMusic();
         }
         //If the music is playing
         else
         {
             //Pause the music
             Mix_PauseMusic();
         }
     }
}

void Sound::loadSFX(const char * filepath){
    this->wave = Mix_LoadWAV(filepath);
}

void Sound::playSFX(){
    Mix_PlayChannel( -1, wave, 0 );
}

void Sound::stopMusic(){
    Mix_HaltMusic();
}
/*Sound::~Sound(){
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
}*/

/*void Sound::loadMusic(const char* filepath){
    printf(" %s \n", filepath);
    if (SDL_LoadWAV(filepath, &wavSpec, &wavBuffer, &wavLength) == NULL){
    SDL_Log("Failed load WAV %s", SDL_GetError());
    } else{
        printf("HEY WAV LOADED");
    }
    this->deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, &wavHave, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
    if (this->deviceId == 0) {
    SDL_Log("Failed to open audio: %s", SDL_GetError());
    }
    printf("loaded one \n");
    printf("WavBuffer %x \n", *wavBuffer);
    printf("WavLength %x \n", wavLength);
}*/

/*void Sound::playMusic(){
    int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    if(success < 0){
        printf("SDL_Queue Failed: %s \n", SDL_GetError());
    }
    SDL_PauseAudioDevice(deviceId, 0);
}*/

/*void Sound::playSFX(){

}*/
