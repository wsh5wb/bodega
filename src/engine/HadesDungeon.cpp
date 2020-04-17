#include "HadesDungeon.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

HadesDungeon::HadesDungeon() {

	id = "HadesDungeon";

	scenes.push_back("./resources/scenes/hades?/basic_room.txt");
	scenes.push_back("./resources/scenes/hades?/start.txt");
	scenes.push_back("./resources/scenes/hades?/basic_room2.txt");
	scenes.push_back("./resources/scenes/hades?/basic_room.txt");
	scenes.push_back("./resources/scenes/hades?/basic_room.txt");
	scenes.push_back("./resources/scenes/hades?/basic_room.txt");
}

HadesDungeon::~HadesDungeon() {
//	for (int i = 0; i < 5; i++)
//		delete layout[i];
//	delete layout;
}

void HadesDungeon::update(set<SDL_Scancode> pressedKeys) {
	Dungeon::update(pressedKeys);
}
void HadesDungeon::draw(AffineTransform &at) {
	Dungeon::draw(at);
}

void HadesDungeon::generate() {
	Dungeon::generate();
}

