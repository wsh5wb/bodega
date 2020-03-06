#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <Animations.h>
#include <ctime>
#include <iostream>

using namespace std;

class AnimatedSprite : public Sprite{

public:
	
	AnimatedSprite();
	AnimatedSprite(string id);
	AnimatedSprite(string id, string filepath);
	//AnimatedSprite(string id, string sheetpath, string xmlpath);
	~AnimatedSprite();

	void addAnimation(string basepath, string animName, int numFrames, int frameRate, bool loop);
	void addAnimation(string sheetpath, string xmlpath, string animName, int numFrames, int frameRate, bool loop);
	Animation* getAnimation(string animName);

	void play(string animName);
	void replay();
	void stop();

	void setFrameRate(int rate);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	bool playing = false;
	int curFrame = 0;
	int frameRate, startIndex, endIndex, numFrames;
	std::clock_t start;
	bool loop, usesSheet;

private:
	unordered_map<string,Animation*> animationMap;
	vector<SDL_Surface*> images;
	vector<SDL_Rect> locations;
};

#endif