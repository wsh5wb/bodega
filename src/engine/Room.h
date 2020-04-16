#ifndef ROOM_H
#define ROOM_H

#include "DisplayObjectContainer.h"
#include "Scene.h"

using namespace std;

class Room: public DisplayObjectContainer {

public:

	Room(string scene);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	bool active = false;
	bool start = false;
	bool visible = false; //draws scene if visible, updates and draws if active
	Scene *room = NULL; //scene that room draws

private:

};

#endif
