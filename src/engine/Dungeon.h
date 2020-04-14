#ifndef DUNGEON_H
#define DUNGEON_H

#include "DisplayObjectContainer.h"
#include "Room.h"

using namespace std;

class Dungeon : public DisplayObjectContainer{

public:

	virtual void update(set<SDL_Scancode> pressedKeys)=0;
	virtual void draw(AffineTransform &at)=0;

	virtual void generate()=0;//sets up layout, reads in scenes, generates rooms

	int ** layout; //2d int array representing dungeon structure where -1 is empty and each other int is index into scenes for that room's corrosponding scene
	vector<string> scenes;//list of paths to scenes representing rooms in dungeon

private:

};

#endif
