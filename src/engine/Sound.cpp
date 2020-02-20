#include "Sound.h"

Sound::Sound(){

}

Sound::~Sound(){
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
}

void Sound::loadMusic(const char* filepath){
    printf(" %s \n", filepath);
    SDL_LoadWAV(filepath, &wavSpec, &wavBuffer, &wavLength);
    deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    printf("loaded one \n");
    printf("WavBuffer %x \n", wavBuffer);
    printf("WavLength %x \n", wavLength);
}

void Sound::playMusic(){
    int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    if(success = 0){
    printf("I tried to play music.\n");
    }else{
        printf("I failed playing music. \n");
    }
    SDL_PauseAudioDevice(deviceId, 0);
}

void Sound::playSFX(){

}