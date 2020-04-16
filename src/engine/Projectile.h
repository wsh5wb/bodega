#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Sprite.h"
#include <ctime>

using namespace std;

class Projectile : public Sprite{
public:
	Projectile();
	//Particle(int red, int green, int blue, int w, int h);
	//Particle(string id, string path);
	Projectile(string path, int x, int y, int speedX, int speedY, int timeout, double scaleX, double scaleY);
	//Particle(string path, int x, int y, int lowX, int highX, int lowY, int highY, int timeout, double scaleX, double scaleY);

	virtual void update(set<SDL_Scancode> pressedKeys);

	std::clock_t start;
	int timeout;
	int speedX, speedY;

private:
};

#endif