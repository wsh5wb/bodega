#ifndef HADESDUNGEON_H
#define HADESDUNGEON_H

#include "Dungeon.h"

using namespace std;

class HadesDungeon: public Dungeon {

public:

	HadesDungeon();
	~HadesDungeon();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	virtual void generate(); //sets up layout, reads in scenes, generates rooms


private:

};

#endif
