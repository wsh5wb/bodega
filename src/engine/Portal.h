#ifndef PORTAL_H
#define PORTAL_H

#include "AnimatedSprite.h"

class Portal : public AnimatedSprite{
public:
	Portal();
	~Portal();

	virtual void draw(AffineTransform &at);
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void saveSelf(vector<string> &objects, vector<string> &dependencies);

private:
};

#endif