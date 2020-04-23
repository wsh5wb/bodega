#include "OceanDungeon.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

OceanDungeon::OceanDungeon() {

	id = "OceanDungeon";

	basic_rooms_size = 4;
	int basic_rooms0[] = { 0, 2, 3, 4 };
	basic_rooms = (int*) malloc(sizeof(int) * basic_rooms_size);
	for (int i = 0; i < basic_rooms_size; i++) {
		basic_rooms[i] = basic_rooms0[i];
	}

	scenes.push_back("./resources/scenes/ocean/basic_room.txt");
	scenes.push_back("./resources/scenes/ocean/start.txt");
	scenes.push_back("./resources/scenes/ocean/basic_room.txt");
	scenes.push_back("./resources/scenes/ocean/basic_room.txt");
	scenes.push_back("./resources/scenes/ocean/jelly_room.txt");
}

OceanDungeon::~OceanDungeon() {
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

