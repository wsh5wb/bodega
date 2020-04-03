#ifndef DUNGEON_H
#define DUNGEON_H

#include "DisplayObjectContainer.h"

using namespace std;

class Dungeon : public DisplayObjectContainer{

public:

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	virtual void saveSelf(vector<string> &objects, vector<string> &dependencies);

	virtual void generate()=0;//sets up layout, reads in scenes, generates rooms

	int ** layout; //2d int array representing dungeon structure where -1 is empty and each other int is index into scenes for that room's corrosponding scene
	vector<string> scenes;//list of paths to scenes representing rooms in dungeon

private:

};

#endif
