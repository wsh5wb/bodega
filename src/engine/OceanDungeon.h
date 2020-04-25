#ifndef OCEANDUNGEON_H
#define OCEANDUNGEON_H

#include "Dungeon.h"

using namespace std;

class OceanDungeon: public Dungeon {

public:

	OceanDungeon();
	~OceanDungeon();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	virtual void generate(); //sets up layout, reads in scenes, generates rooms


private:
	Sound ocean_theme;
};

#endif
