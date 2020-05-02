#ifndef PORTAL_H
#define PORTAL_H

#include "AnimatedSprite.h"
#include "EventListener.h"

class Portal : public AnimatedSprite, EventListener{
public:
	Portal();
	~Portal();

	virtual void draw(AffineTransform &at);
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void saveSelf(vector<string> &objects, vector<string> &dependencies);
	virtual void handleEvent(Event* e);

private:
};

#endif