#ifndef ROOM_H
#define ROOM_H

#include "DisplayObjectContainer.h"

using namespace std;

class Room : public DisplayObjectContainer{

public:

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	virtual void saveSelf(vector<string> &objects, vector<string> &dependencies);

	bool active, visable;//draws scene if visible, updates and draws if active
	Scene room; //scene that room draws

private:

};

#endif
