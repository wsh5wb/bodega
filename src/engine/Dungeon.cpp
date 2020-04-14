#include "Dungeon.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Dungeon::~Dungeon() {
	for (int i = 0; i < 5; i++)
		delete layout[i];
	delete layout;
}

void Dungeon::update(set<SDL_Scancode> pressedKeys) {
	DisplayObjectContainer::update(pressedKeys);
}
void Dungeon::draw(AffineTransform &at) {
	DisplayObjectContainer::draw(at);
}

void Dungeon::generate() {
	//sets up layout, reads in scenes, generates rooms
	//layout = NULL;//replace with output from generate.cpp
	layout = new int*[5];
	for (int i = 0; i < 5; i++) {
		layout[i] = new int[5];
		for (int j = 0; j < 5; j++) {
			layout[i][j] = !(i + j);
		}
	}

	for (int i = 5; i--;) {
		for (int j = 5; j--;) {
			int ind = layout[i][j];
			string s = this->scenes.at(ind);
			Room *temp = new Room(s); //crashes here???
			temp->id = id + to_string(i) + "-" + to_string(j);
			temp->moveTo(1200 * j, 900 * i);
			if (!(i + j)) {
				temp->active = true;
			}
			DisplayObjectContainer::addChild(temp);
		}
	}
}

