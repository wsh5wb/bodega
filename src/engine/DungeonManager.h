#ifndef DUNGEONMANAGER_H
#define DUNGEONMANAGER_H

#include "Dungeon.h"
#include "HadesDungeon.h"
#include "OceanDungeon.h"

#define NUM_DUNGEONS	2
#define HADES		 	0
#define OCEAN			1

class DungeonManager : EventListener{
public:
	virtual void handleEvent(Event* e){
		if(e->getType() == "CHANGE_DUNGEON"){
			printf("Changing dungeon\n");
			Camera::getCamera()->removeScene(activeDungeon);
			// delete activeDungeon;
			switch(curr_dungeon){
				case HADES: {
					printf("GENERATING OCEAN\n");
					activeDungeon = new OceanDungeon();
					activeDungeon->generate();
					curr_dungeon = OCEAN;
					break;
				}
				case OCEAN: {
					printf("GENERATING HADES\n");
					activeDungeon = new HadesDungeon();
					activeDungeon->generate();
					curr_dungeon = HADES;
					break;
				}
			}

			Camera::getCamera()->addScene(activeDungeon);
			// curr_dungeon = (curr_dungeon+1)%NUM_DUNGEONS;
		}
	} 

	Dungeon* activeDungeon = NULL;
	unsigned char curr_dungeon = HADES;
	// probably put num dungeons in define statement somewhere
	Dungeon* dungeons[NUM_DUNGEONS];
};

#endif