#include "ForestDungeon.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

ForestDungeon::ForestDungeon() {

	id = "ForestDungeon";

	basic_rooms_size = 5;
	int basic_rooms0[] = { 0, 2, 3, 4, 5 };
	basic_rooms = (int*) malloc(sizeof(int) * basic_rooms_size);
	for (int i = 0; i < basic_rooms_size; i++) {
		basic_rooms[i] = basic_rooms0[i];
	}

	scenes.push_back("./resources/scenes/ocean/basic_room.txt");
	scenes.push_back("./resources/scenes/ocean/start.txt");
	scenes.push_back("./resources/scenes/ocean/basic_room.txt");
	scenes.push_back("./resources/scenes/ocean/basic_room.txt");
	scenes.push_back("./resources/scenes/ocean/jelly_room.txt");
	scenes.push_back("./resources/scenes/ocean/urchin_room.txt");
	// these must go at bottom
	scenes.push_back("./resources/scenes/ocean/boss_top_left.txt");
	scenes.push_back("./resources/scenes/ocean/boss_top_right.txt");
	scenes.push_back("./resources/scenes/ocean/boss_bot_left.txt");
	scenes.push_back("./resources/scenes/ocean/boss_bot_right.txt");
	
}



