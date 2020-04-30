#include "OlympusDungeon.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

OlympusDungeon::OlympusDungeon() {

	id = "OlympusDungeon";

	basic_rooms_size = 6;
	portal_index = 6;
	int basic_rooms0[] = { 0, 2, 3, 4, 5, 7 };
	basic_rooms = (int*) malloc(sizeof(int) * basic_rooms_size);
	for (int i = 0; i < basic_rooms_size; i++) {
		basic_rooms[i] = basic_rooms0[i];
	}
	olympus_dungeon.loadMusic("./resources/sounds/foreign_area4.wav");
	olympus_dungeon.playMusic();
	scenes.push_back("./resources/scenes/olympus/basic_room1.txt");
	scenes.push_back("./resources/scenes/olympus/start.txt");
	scenes.push_back("./resources/scenes/olympus/basic_room1.txt");
	scenes.push_back("./resources/scenes/olympus/torch_chest.txt");
	scenes.push_back("./resources/scenes/olympus/jelly_room.txt");
	scenes.push_back("./resources/scenes/olympus/urchin_room.txt");
	scenes.push_back("./resources/scenes/olympus/portal_room.txt");
	scenes.push_back("./resources/scenes/olympus/spirit_room.txt");
	// these must go at bottom
	scenes.push_back("./resources/scenes/olympus/BossTLC.txt");
	scenes.push_back("./resources/scenes/olympus/BossTRC.txt");
	scenes.push_back("./resources/scenes/olympus/BossBLC.txt");
	scenes.push_back("./resources/scenes/olympus/BossBRC.txt");
}
