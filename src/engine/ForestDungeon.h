#ifndef FORESTDUNGEON_H
#define FORESTDUNGEON_H

#include "Dungeon.h"

using namespace std;

class ForestDungeon: public Dungeon {

public:

	ForestDungeon();
	~ForestDungeon();


private:
	Sound forrest_theme;
};

#endif
