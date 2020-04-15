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

private:

};

#endif
