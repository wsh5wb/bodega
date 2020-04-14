#include "HadesDungeon.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

HadesDungeon::HadesDungeon() {
	layout = new int*[5];
	for (int i = 0; i < 5; i++) {
		layout[i] = new int[5];
		for (int j = 0; j < 5; j++) {
				layout[i][j] = !(i+j);
		}
	}

	scenes.push_back("./resources/scenes/hades?/basic_room.txt");
	scenes.push_back("./resources/scenes/hades?/start.txt");
}

HadesDungeon::~HadesDungeon() {
	for (int i = 0; i < 5; i++)
		delete layout[i];
	delete layout;
}

void HadesDungeon::update(set<SDL_Scancode> pressedKeys) {
	DisplayObjectContainer::update(pressedKeys);
}
void HadesDungeon::draw(AffineTransform &at) {
	DisplayObjectContainer::draw(at);
}

void HadesDungeon::generate() {
	//sets up layout, reads in scenes, generates rooms
	for (int i = 5; i--;) {
		for (int j = 5; j--;) {
			int ind = layout[i][j];
			string s = scenes.at(ind);
			Room *temp = new Room(s); //crashes here???
			temp->id = "HadesDungeon_" + to_string(i) + "-" + to_string(j);
			temp->moveTo(1200 * j, 900 * i);
			if (!(i + j)) {
				temp->active = true;
			}
			DisplayObjectContainer::addChild(temp);
		}
	}
}

