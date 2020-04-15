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
	MazeGenerator *M = new MazeGenerator();
	cerr << "here0\n";
	layout = (int**) (M->getLayout());
	for (int i = GRID_SIZE; i--;) {
		for (int j = GRID_SIZE; j--;) {
			layout[i][j]-=1;
		}
	}
	cerr << "here1\n";
	for (int i = GRID_SIZE; i--;) {
		for (int j = GRID_SIZE; j--;) {
			int ind = layout[i][j];
			if (ind >= 0) {
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
	cerr << "here2\n";
}

