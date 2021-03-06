#include "OceanDungeon.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

OceanDungeon::OceanDungeon() {

	id = "OceanDungeon";

	basic_rooms_size = 6;
	portal_index = 6;
	int basic_rooms0[] = { 0, 2, 3, 4, 5, 7 };
	basic_rooms = (int*) malloc(sizeof(int) * basic_rooms_size);
	for (int i = 0; i < basic_rooms_size; i++) {
		basic_rooms[i] = basic_rooms0[i];
	}
	ocean_theme.loadMusic("./resources/sounds/lastfish_area2.wav");
	ocean_theme.playMusic();
	scenes.push_back("./resources/scenes/ocean/water_jelly.txt");
	scenes.push_back("./resources/scenes/ocean/start.txt");
	scenes.push_back("./resources/scenes/ocean/water_spirit.txt");
	scenes.push_back("./resources/scenes/ocean/water_spirit2.txt");
	scenes.push_back("./resources/scenes/ocean/jelly_room.txt");
	scenes.push_back("./resources/scenes/ocean/urchin_room.txt");
	scenes.push_back("./resources/scenes/ocean/portal_room.txt");
	scenes.push_back("./resources/scenes/ocean/water_chest.txt");
	// these must go at bottom
	scenes.push_back("./resources/scenes/ocean/boss_top_left.txt");
	scenes.push_back("./resources/scenes/ocean/boss_top_right.txt");
	scenes.push_back("./resources/scenes/ocean/boss_bot_left.txt");
	scenes.push_back("./resources/scenes/ocean/boss_bot_right.txt");
}

OceanDungeon::~OceanDungeon() {
	free(basic_rooms);
//	for (int i = 0; i < 5; i++)
//		delete layout[i];
//	delete layout;
}

void OceanDungeon::update(set<SDL_Scancode> pressedKeys) {
	Dungeon::update(pressedKeys);
}
void OceanDungeon::draw(AffineTransform &at) {
	Dungeon::draw(at);
}

void OceanDungeon::generate() {
	Dungeon::generate();
}
