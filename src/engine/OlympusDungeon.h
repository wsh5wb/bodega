#ifndef OLYMPUSDUNGEON_H
#define OLYMPUSDUNGEON_H

#include "Dungeon.h"

using namespace std;

class OlympusDungeon: public Dungeon {

public:

	OlympusDungeon();
	~OlympusDungeon();


private:
	Sound olympus_dungeon;
};

#endif
