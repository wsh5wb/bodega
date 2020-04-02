#ifndef PARTICLE_H
#define PARTICLE_H

#include "Sprite.h"
#include <ctime>

using namespace std;

class Particle : public Sprite{
public:
	Particle();
	Particle(int red, int green, int blue, int w, int h);
	Particle(string id, string path);
	Particle(string path, int x, int y, int speedX, int speedY, int timeout, double scaleX, double scaleY);
	Particle(string path, int x, int y, int lowX, int highX, int lowY, int highY, int timeout, double scaleX, double scaleY);

	virtual void update(set<SDL_Scancode> pressedKeys);

	std::clock_t start;
	int timeout, generateTime;
	int speedX, speedY;
	int lowX, lowY;
	bool rand;

private:
};

#endif