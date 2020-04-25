#ifndef DUNGEONMANAGER_H
#define DUNGEONMANAGER_H

#include "Dungeon.h"
#include "HadesDungeon.h"
#include "OceanDungeon.h"
#include "ForestDungeon.h"
#include "OlympusDungeon.h"

#define NUM_DUNGEONS	4
#define HADES		 	0
#define OCEAN			1
#define FOREST		 	2
#define OLYMPUS			3

#define FLOORS_PER_DUNGEON 2

class DungeonManager: EventListener {
public:
	virtual void handleEvent(Event *e) {
		if (e->getType() == "CHANGE_DUNGEON") {
			printf("Changing dungeon\n");
			Camera::getCamera()->removeScene(activeDungeon);
			// delete activeDungeon;
			switch (curr_dungeon) {
			case HADES: {
				curr_floor++;
				if (curr_floor < FLOORS_PER_DUNGEON) {
					printf("GENERATING HADES\n");
					activeDungeon = new HadesDungeon();
					curr_dungeon = HADES;
					activeDungeon->dungeonType = curr_dungeon;
					if (curr_floor == FLOORS_PER_DUNGEON - 1) {
						activeDungeon->generate();
					} else {
						activeDungeon->generateNoBoss();
					}
					cerr << "no boss hades\n";
				} else {
					printf("GENERATING OCEAN\n");
					activeDungeon = new OceanDungeon();
					curr_dungeon = OCEAN;
					activeDungeon->dungeonType = curr_dungeon;
					activeDungeon->generateNoBoss();
					curr_floor = 0;
					cerr << "boss hades\n";
				}

				break;
			}
			case OCEAN: {
				curr_floor++;
				if (curr_floor < FLOORS_PER_DUNGEON) {
					printf("GENERATING OCEAN\n");
					activeDungeon = new OceanDungeon();
					curr_dungeon = OCEAN;
					activeDungeon->dungeonType = curr_dungeon;
					if (curr_floor == FLOORS_PER_DUNGEON - 1) {
						activeDungeon->generate();
					} else {
						activeDungeon->generateNoBoss();
					}
				} else {
					printf("GENERATING FOREST\n");
					activeDungeon = new ForestDungeon();
					curr_dungeon = FOREST;
					activeDungeon->dungeonType = curr_dungeon;
					activeDungeon->generateNoBoss();
					curr_floor = 0;
				}

				break;
			}
			case FOREST: {
				curr_floor++;
				if (curr_floor < FLOORS_PER_DUNGEON) {
					printf("GENERATING FOREST\n");
					activeDungeon = new ForestDungeon();
					curr_dungeon = FOREST;
					activeDungeon->dungeonType = curr_dungeon;
					if (curr_floor == FLOORS_PER_DUNGEON - 1) {
						activeDungeon->generate();
					} else {
						activeDungeon->generateNoBoss();
					}
				} else {
					printf("GENERATING OLYMPUS\n");
					activeDungeon = new OlympusDungeon();
					curr_dungeon = OLYMPUS;
					activeDungeon->dungeonType = curr_dungeon;
					activeDungeon->generateNoBoss();
					curr_floor = 0;
				}

				break;
			}
			case OLYMPUS: {
				curr_floor++;
				if (curr_floor < FLOORS_PER_DUNGEON) {
					printf("GENERATING OLYMPUS\n");
					activeDungeon = new OlympusDungeon();
					curr_dungeon = OLYMPUS;
					activeDungeon->dungeonType = curr_dungeon;
					if (curr_floor == FLOORS_PER_DUNGEON - 1) {
						activeDungeon->generate();
					} else {
						activeDungeon->generateNoBoss();
					}
				} else {
					printf("GENERATING HADES\n");
					activeDungeon = new HadesDungeon();
					curr_dungeon = HADES;
					activeDungeon->dungeonType = curr_dungeon;
					activeDungeon->generateNoBoss();
					curr_floor = 0;
				}

				break;
			}
			}

			Camera::getCamera()->addScene(activeDungeon);
			// curr_dungeon = (curr_dungeon+1)%NUM_DUNGEONS;
		} else if (e->getType() == "PLAYER_KILLED") {
			printf("Changing dungeon (on death)\n");
			Camera::getCamera()->removeScene(activeDungeon);
			printf("GENERATING HADES (on death)\n");
			activeDungeon = new HadesDungeon();
			curr_dungeon = HADES;
			activeDungeon->dungeonType = curr_dungeon;
			curr_floor = 1;
			if (curr_floor < FLOORS_PER_DUNGEON) {
				activeDungeon->generateNoBoss();
			} else {
				activeDungeon->generate();
			}
			Camera::getCamera()->addScene(activeDungeon);
		}
	}

	Dungeon *activeDungeon = NULL;
	unsigned char curr_dungeon = HADES;

	unsigned char curr_floor = 0;
	// probably put num dungeons in define statement somewhere
	Dungeon *dungeons[NUM_DUNGEONS];
};

#endif
