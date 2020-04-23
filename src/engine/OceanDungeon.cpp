#include "OceanDungeon.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

OceanDungeon::OceanDungeon(){

	id = "OceanDungeon";

	scenes.push_back("./resources/scenes/ocean/basic_room.txt");
	scenes.push_back("./resources/scenes/ocean/start.txt");
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

