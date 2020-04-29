#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "AnimatedSprite.h"
#include <ctime>

using namespace std;

class Projectile : public AnimatedSprite{
public:
	Projectile();
	~Projectile();
	Projectile(int my_type, int x, int y, int speedX, int speedY, int timeout, double scaleX, double scaleY);
	Projectile(string path, int x, int y, int speedX, int speedY, int timeout, double scaleX, double scaleY, int damage);
	//Particle(sting path, int x, int y, int lowX, int highX, int lowY, int highY, int timeout, double scaleX, double scaleY);
	virtual void draw(AffineTransform &at);
	virtual void update(set<SDL_Scancode> pressedKeys);
	int getMyType();
	int getDamage();

	std::clock_t start;
	int timeout;
	int speedX, speedY;
	int my_type;
	int damage;

private:

};

#endif
