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
		auto find = pressedKeys.find(SDL_SCANCODE_W);
		if(find != pressedKeys.end()) {
			if(!zoomed_out) {
				cerr << "here 17\n";
				zoomed_out = true;
				Camera* myCamera = Camera::getCamera();
				myCamera->setLocation(0,0);

				myCamera->setZoom(500/GRID_SIZE, 500/GRID_SIZE);
			}
		} else {
			if(zoomed_out) {
				zoomed_out = false;
				Camera* myCamera = Camera::getCamera();
				myCamera->setLocation(1200*current_x,900*current_y);
				myCamera->setZoom(500, 500);
			}
		}
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
				if (layout[i][j] == START_ROOM) {
					start_x = current_x = j;
					start_y = current_y = i;
				}
				layout[i][j] -= 1;
			}
		}
		cerr << "here1\n";
		Room *start_room;
		for (int i = GRID_SIZE; i--;) {
			for (int j = GRID_SIZE; j--;) {
				int ind = layout[i][j];
				if (ind >= 0) {
					string s = this->scenes.at(ind);
					Room *temp = new Room(s); //crashes here???
					temp->id = id + to_string(i) + "-" + to_string(j);
					temp->moveTo(1200 * j, 900 * i);
					if (start_x == j && start_y == i) {
						temp->active = true;
						start_room = temp;
					} else {
						DisplayObjectContainer::addChild(temp);
					}
				}
			}
		}
		DisplayObjectContainer::addChild(start_room);
		cerr << "here2\n";
	}

