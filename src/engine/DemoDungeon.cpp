#include "DemoDungeon.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

DemoDungeon::DemoDungeon() {
	layout = new int*[2];
	for (int i = 0; i < 2; i++) {
		layout[i] = new int[2];
		for (int j = 0; j < 2; j++) {
			if (i + j)
				layout[i][j] = 0;
			else
				layout[i][j] = 1;
		}
	}

	cerr << "constructing\n";
	scenes.push_back("./resources/scenes/hades?/basic_room.txt");
	scenes.push_back("./resources/scenes/hades?/start.txt");
}

DemoDungeon::~DemoDungeon() {
	for (int i = 0; i < 2; i++)
		delete layout[i];
	delete layout;
}

void DemoDungeon::update(set<SDL_Scancode> pressedKeys) {
	DisplayObjectContainer::update(pressedKeys);
}
void DemoDungeon::draw(AffineTransform &at) {
	DisplayObjectContainer::draw(at);
}

void DemoDungeon::generate() {
	//sets up layout, reads in scenes, generates rooms
	cerr << "generating0\n";
	layout[0][0] = 1;
	layout[0][1] = 0;
	layout[1][0] = 0;
	layout[1][1] = 0;
	cerr << "generating1\n";
	for (int i = 2; i--;) {
		for (int j = 2; j--;) {
			cerr << "generating3\n";
			int ind = layout[i][j];
			cerr << "generating4\n";
			string s = scenes.at(ind);
			cerr << "generating5 " << s << "\n";
			Room *temp = new Room(s,0,0); //crashes here???
			cerr << "generating6\n";
			temp->id = "DemoDungeon_" + to_string(i) + "-" + to_string(j);
			cerr << "generating7\n";
			temp->moveTo(1200 * j, 900 * i);
			cerr << "generating8\n";
			if (!(i + j)) {
				temp->active = true;
			}
			DisplayObjectContainer::addChild(temp);
		}
	}
	cerr << "generating2\n";
}

