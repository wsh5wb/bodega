#include "HadesDungeon.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

HadesDungeon::HadesDungeon() {

	//might not need
	layout = new int*[5];
	for (int i = 0; i < 5; i++) {
		layout[i] = new int[5];
		for (int j = 0; j < 5; j++) {
			layout[i][j] = !(i + j);
		}
	}
	id = "HadesDungeon";

	scenes.push_back("./resources/scenes/hades?/basic_room.txt");
	scenes.push_back("./resources/scenes/hades?/start.txt");
}

HadesDungeon::~HadesDungeon() {
	for (int i = 0; i < 5; i++)
		delete layout[i];
	delete layout;
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

