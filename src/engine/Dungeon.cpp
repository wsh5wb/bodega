#include "Dungeon.h"
#include "TweenJuggler.h"
#include "Camera.h"
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
	auto find = pressedKeys.find(SDL_SCANCODE_M);
	if (find != pressedKeys.end()) {
		if (!zoomed_out) {
			zoomed_out = true;
			Camera *myCamera = Camera::getCamera();
			myCamera->setLocation(0, 0);

			myCamera->setZoom(500 / GRID_SIZE, 500 / GRID_SIZE);
		}
	} else {
		if (zoomed_out) {
			zoomed_out = false;
			Camera *myCamera = Camera::getCamera();
			myCamera->setLocation(1200 * current_x, 900 * current_y);
			myCamera->setZoom(500, 500);
		}
	}

	find = pressedKeys.find(SDL_SCANCODE_V);
	if (find != pressedKeys.end()) {
		for (auto c : children) {
			((Room*) (c))->visible = true;
		}
	}

	find = pressedKeys.find(SDL_SCANCODE_N);
	if (find != pressedKeys.end()) {
		Player *p = Player::getPlayer();
		p->moveTo(224, 224);
		current_x = start_x;
		current_y = start_y;
		zoomed_out = true;

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

	floor_t level = M->getLevel();
	cerr << "here1\n";
	Room *start_room;
	for (int i = GRID_SIZE; i--;) {
		for (int j = GRID_SIZE; j--;) {
			int ind = layout[i][j];
			if (ind >= 0) {
				printf("room at (%d,%d) ", j,i);
				room_t* room_data = level.rooms["("+to_string(i)+","+to_string(j)+")"];
				int c = 0;
				unsigned char doors = room_data->doors;
				printf("doors %x\n", doors);
				string s = this->scenes.at(ind);
				Room *temp = new Room(s, doors); //crashes here???
				temp->id = id + to_string(i) + "-" + to_string(j);
				temp->moveTo(1200 * j, 900 * i);
				
				if (start_x == j && start_y == i) {
					temp->active = true;
					temp->start = true;
					temp->visible = true;
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

void Dungeon::handleEvent(Event *e) {
	string type = e->getType();
	Room *old_room = (Room*) DisplayObjectContainer::getChild(
			id + to_string(current_y) + "-" + to_string(current_x));
	if (!old_room) {
		// cerr << "player not in valid room\n";
		return;
	}
	int field;
	double startPos, endPos;
	Player *player = Player::getPlayer();
	// printf("before transition, curr x and y are %d     %d\n", current_x, current_y);

	if (type == "DUNG_TRANS_D") {
		startPos = 900 * current_y;
		current_y += 1;
		field = TWEEN_POSITION_Y;
		endPos = 900 * current_y;
		player->translate(0, 100);
		old_room->active = false;
		Room *new_room = (Room*) DisplayObjectContainer::getChild(
				id + to_string(current_y) + "-" + to_string(current_x));
		if (new_room) {
			cerr << id + to_string(current_y) + "-" + to_string(current_x);
			new_room->active = true;
			new_room->visible = true;
		}
	} else if (type == "DUNG_TRANS_L") {
		startPos = 1200 * current_x;
		current_x -= 1;
		field = TWEEN_POSITION_X;
		endPos = 1200 * current_x;
		player->translate(-100, 0);
		old_room->active = false;
		Room *new_room = (Room*) DisplayObjectContainer::getChild(
				id + to_string(current_y) + "-" + to_string(current_x));
		if (new_room) {
			cerr << id + to_string(current_y) + "-" + to_string(current_x);
			new_room->active = true;
			new_room->visible = true;
		}
	} else if (type == "DUNG_TRANS_U") {
		startPos = 900 * current_y;
		current_y -= 1;
		field = TWEEN_POSITION_Y;
		endPos = 900 * current_y;
		player->translate(0, -100);
		old_room->active = false;
		Room *new_room = (Room*) DisplayObjectContainer::getChild(
				id + to_string(current_y) + "-" + to_string(current_x));
		if (new_room) {
			cerr << id + to_string(current_y) + "-" + to_string(current_x);
			new_room->active = true;
			new_room->visible = true;
		}
	} else if (type == "DUNG_TRANS_R") {
		startPos = 1200 * current_x;
		current_x += 1;
		field = TWEEN_POSITION_X;
		endPos = 1200 * current_x;
		player->translate(100, 0);
		old_room->active = false;
		Room *new_room = (Room*) DisplayObjectContainer::getChild(
				id + to_string(current_y) + "-" + to_string(current_x));
		if (new_room) {
			cerr << id + to_string(current_y) + "-" + to_string(current_x);
			new_room->active = true;
			new_room->visible = true;
		}
	}

//	Tween *playerPosTween = new Tween(player);
	TweenJuggler *juggler = TweenJuggler::getInstance();
//	playerPosTween->animate(field, player->position.x, player->position.x + (((int)(endPos-startPos)>>31)^100), 100, TWEEN_LINEAR, EASE_IN);
//	juggler->add(playerPosTween);

	// no tweening until we add functionality to tween camera
	Camera *myCamera = Camera::getCamera();
	if (!zoomed_out) {
		printf("after transition, curr x and y are %d     %d\n", current_x,
				current_y);
		Tween *camPosTween = new Tween(Camera::getCamera()->container);
		camPosTween->animate(field, -startPos, -endPos, 30, TWEEN_LINEAR,
				EASE_INOUT);
		juggler->add(camPosTween);
	}

}
