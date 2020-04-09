#ifndef DEMODUNGEON_H
#define DEMODUNGEON_H

#include "Dungeon.h"

using namespace std;

class DemoDungeon: public Dungeon {

public:

	DemoDungeon();
	~DemoDungeon();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	virtual void generate(); //sets up layout, reads in scenes, generates rooms

	int **layout; //2d int array representing dungeon structure where -1 is empty and each other int is index into scenes for that room's corrosponding scene
	vector<string> scenes; //list of paths to scenes representing rooms in dungeon
private:

};

#endif
