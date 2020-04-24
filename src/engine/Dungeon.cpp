#include "Dungeon.h"
#include "TweenJuggler.h"
#include "Camera.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "HadesDungeon.h"

using namespace std;

Dungeon::Dungeon() {
	Game::eventHandler.addEventListener((EventListener*) this, "DUNG_TRANS_U");
	Game::eventHandler.addEventListener((EventListener*) this, "DUNG_TRANS_D");
	Game::eventHandler.addEventListener((EventListener*) this, "DUNG_TRANS_R");
	Game::eventHandler.addEventListener((EventListener*) this, "DUNG_TRANS_L");
	Game::eventHandler.addEventListener((EventListener*) this, "ENEMY_KILLED");
	Game::eventHandler.addEventListener((EventListener*) this, "PLAYER_KILLED");

}
Dungeon::~Dungeon() {
	cerr << "DUNGEON DESTRUCTOR" << endl;
	Game::eventHandler.removeEventListener((EventListener*) this,
			"DUNG_TRANS_U");
	Game::eventHandler.removeEventListener((EventListener*) this,
			"DUNG_TRANS_D");
	Game::eventHandler.removeEventListener((EventListener*) this,
			"DUNG_TRANS_R");
	Game::eventHandler.removeEventListener((EventListener*) this,
			"DUNG_TRANS_L");
	Game::eventHandler.removeEventListener((EventListener*) this,
			"ENEMY_KILLED");
	Game::eventHandler.removeEventListener((EventListener*) this,
			"PLAYER_KILLED");
	cleanMatrix(layout);
}

void Dungeon::cleanMatrix(int **m) {
	for (int i = 0; i < GRID_SIZE; i++)
		delete m[i];
	delete m;
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

	//camera for being in dungeon
	if (!zoomed_out && current_x == boss_x && current_y == boss_y) {
		int room_size_x = 512;
		int room_size_y = 384;
		int x_adj = (boss_x - start_x) * room_size_x;
		int y_adj = (boss_y - start_y) * room_size_y;
		Player *p = Player::getPlayer();
		Camera *myCamera = Camera::getCamera();
		int c_x = -myCamera->container->position.x;
		int c_y = -myCamera->container->position.y;
		if (p->position.x - x_adj < (room_size_x / 2)
				&& p->position.x - x_adj > (-room_size_x / 2)) {
			c_x = 1200 * current_x + 2.34375 * (p->position.x - x_adj) - 600;
		} else if (p->position.x - x_adj > (-room_size_x / 2)) {
			c_x = 1200 * (current_x);
		} else {
			c_x = 1200 * (current_x - 1);
		}
		if (p->position.y - y_adj < (room_size_y / 2)
				&& p->position.y - y_adj > (-room_size_y / 2)) {
			c_y = 900 * current_y + 2.34375 * (p->position.y - y_adj) - 450;
		} else if (p->position.y - y_adj > (-room_size_y / 2)) {
			c_y = 900 * (current_y);
		} else {
			c_y = 900 * (current_y - 1);
		}
		myCamera->setLocation(c_x, c_y);
	}

	for (SDL_Scancode code : pressedKeys) {
		switch (code) {

		case SDL_SCANCODE_V: {
			for (auto c : children) {
				((Room*) (c))->visible = true;
			}
			break;
		}

		case SDL_SCANCODE_N: {
			if (DEBUG_CHANGE_ROOM) {
				DEBUG_CHANGE_ROOM = false;

				Player *p = Player::getPlayer();
				p->moveTo(224, 224);
				Room *old_room = (Room*) DisplayObjectContainer::getChild(
						id + to_string(current_y) + "-" + to_string(current_x));
				old_room->active = false;
				current_x = start_x;
				current_y = start_y;
				Room *start_room = (Room*) DisplayObjectContainer::getChild(
						id + to_string(current_y) + "-" + to_string(current_x));
				start_room->active = true;
				start_room->openDoors();

				zoomed_out = true;
			}
			break;
		}

		case SDL_SCANCODE_I: {
			if (DEBUG_CHANGE_ROOM) {
				DEBUG_CHANGE_ROOM = false;
				current_y -= 1;
				zoomed_out = true;
				cerr << "setting location to: (" << current_x << ", "
						<< current_y << ")\n";
			}
			break;
		}

		case SDL_SCANCODE_J: {
			if (DEBUG_CHANGE_ROOM) {
				DEBUG_CHANGE_ROOM = false;
				current_x -= 1;
				zoomed_out = true;
				cerr << "setting location to: (" << current_x << ", "
						<< current_y << ")\n";
			}
			break;
		}

		case SDL_SCANCODE_K: {
			if (DEBUG_CHANGE_ROOM) {
				DEBUG_CHANGE_ROOM = false;
				current_y += 1;
				zoomed_out = true;
				cerr << "setting location to: (" << current_x << ", "
						<< current_y << ")\n";
			}
			break;
		}

		case SDL_SCANCODE_L: {
			if (DEBUG_CHANGE_ROOM) {
				DEBUG_CHANGE_ROOM = false;
				current_x += 1;
				zoomed_out = true;
				cerr << "setting location to: (" << current_x << ", "
						<< current_y << ")\n";
			}
			break;
		}

		case SDL_SCANCODE_U: {
			DEBUG_CHANGE_ROOM = true;
			break;
		}

		case SDL_SCANCODE_C: {
			Player *p = Player::getPlayer();
			cerr << "player x: " << p->position.x;
			cerr << "\nplayer y: " << p->position.y << "\n\n";
			break;
		}

		}
	}
	if (changingRoom) {
		if (timer <= ROOM_START_DELAY) {
			timer++;
		} else {
			zoomed_out = true;
			changingRoom->active = true;
			changingRoom = NULL;
			timer = 0;
		}
	}
}

void Dungeon::draw(AffineTransform &at) {
	DisplayObjectContainer::draw(at);
}

void Dungeon::generate() {

	Game::cs->watchForCollisions("PLAYER", "DOOR");
	MazeGenerator M;
	cerr << "here0\n";
	layout = (int**) (M.getLayout());
	srand (time(NULL));for
(	int i = GRID_SIZE; i--;) {
		for (int j = GRID_SIZE; j--;) {
			if (layout[i][j] == START_ROOM) {
				start_x = current_x = j;
				start_y = current_y = i;
			}
			layout[i][j] -= 1;
			if(!(layout[i][j]) && basic_rooms_size > 0) {
				int ind = rand()%basic_rooms_size;
				layout[i][j] = basic_rooms[ind];
			}
		}
	}

	floor_t level = M.getLevel();
	cerr << "here1\n";
	Room *start_room;
	for (int i = GRID_SIZE; i--;) {
		for (int j = GRID_SIZE; j--;) {
			int ind = layout[i][j];
			if (ind >= 0) {
				// printf("room at (%d,%d) ", j, i);
				room_t *room_data = level.rooms["(" + to_string(i) + ","
						+ to_string(j) + ")"];
				int c = 0;
				unsigned char doors = room_data->doors;
				// printf("doors %x\n", doors);
				if(ind == BOSS_ROOM -1){
					boss_x = j; boss_y = i;
					ind = 0;
				}
				string s = this->scenes.at(ind);
				Room *temp = new Room(s, doors, dungeonType);
				temp->id = id + to_string(i) + "-" + to_string(j);
				temp->moveTo(1200 * j, 900 * i);

				if (start_x == j && start_y == i) {
					printf("Setting start room to active\n");
					temp->active = true;
					temp->start = true;
					temp->visible = true;
					start_room = temp;
					// DisplayObject* portal = 
					// 	new DisplayObject("PORTAL", "./resources/character/floryan_head.png");
					// portal->scale(.25);
					// portal->moveTo(240,180);
					// portal->setHitbox(.1,.9);
					// portal->showHitbox = true;
					// temp->room->addChild(portal);
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
	if (type == "DUNG_TRANS_D" || type == "DUNG_TRANS_L"
			|| type == "DUNG_TRANS_U" || type == "DUNG_TRANS_R") {
		transitionRoom(type);
	} else if (type == "ENEMY_KILLED") {

		Room *activeRoom = (Room*) DisplayObjectContainer::getChild(
				id + to_string(current_y) + "-" + to_string(current_x));

		if (activeRoom->room->numEnemies > 1) {
			activeRoom->room->numEnemies--;
			return;
		}

		activeRoom->room->numEnemies = 0;
		activeRoom->openDoors();
	} else if (type == "PLAYER_KILLED") {
		//do nothing
	}

}

void Dungeon::transitionRoom(string type) {
	Room *old_room = (Room*) DisplayObjectContainer::getChild(
			id + to_string(current_y) + "-" + to_string(current_x));
	if (!old_room) {
		// cerr << "player not in valid room\n";
		return;
	}
	old_room->removeFromDisplayTree();
	int field;
	double startPos, endPos;
	Player *player = Player::getPlayer();
	int player_dist = 90;
	// printf("before transition, curr x and y are %d     %d\n", current_x, current_y);
	Room *new_room;
	if (type == "DUNG_TRANS_D") {
		startPos = 900 * current_y;
		current_y += 1;
		field = TWEEN_POSITION_Y;
		endPos = 900 * current_y;
		old_room->active = false;
		player->translate(0, player_dist);
		new_room = (Room*) DisplayObjectContainer::getChild(
				id + to_string(current_y) + "-" + to_string(current_x));
		if (new_room) {
			cerr << id + to_string(current_y) + "-" + to_string(current_x)
					<< "\n";
			new_room->visible = true;
			new_room->addToDisplayTree();
		}
	} else if (type == "DUNG_TRANS_L") {
		startPos = 1200 * current_x;
		current_x -= 1;
		field = TWEEN_POSITION_X;
		endPos = 1200 * current_x;
		player->translate(-player_dist, 0);
		old_room->active = false;
		new_room = (Room*) DisplayObjectContainer::getChild(
				id + to_string(current_y) + "-" + to_string(current_x));
		if (new_room) {
			cerr << id + to_string(current_y) + "-" + to_string(current_x)
					<< "\n";
			new_room->visible = true;
			new_room->addToDisplayTree();
		}
	} else if (type == "DUNG_TRANS_U") {
		startPos = 900 * current_y;
		current_y -= 1;
		field = TWEEN_POSITION_Y;
		endPos = 900 * current_y;
		player->translate(0, -player_dist);
		old_room->active = false;
		new_room = (Room*) DisplayObjectContainer::getChild(
				id + to_string(current_y) + "-" + to_string(current_x));
		if (new_room) {
			cerr << id + to_string(current_y) + "-" + to_string(current_x)
					<< "\n";
			new_room->visible = true;
			new_room->addToDisplayTree();
		}
	} else if (type == "DUNG_TRANS_R") {
		startPos = 1200 * current_x;
		current_x += 1;
		field = TWEEN_POSITION_X;
		endPos = 1200 * current_x;
		player->translate(player_dist, 0);
		old_room->active = false;
		new_room = (Room*) DisplayObjectContainer::getChild(
				id + to_string(current_y) + "-" + to_string(current_x));
		if (new_room) {
			cerr << id + to_string(current_y) + "-" + to_string(current_x)
					<< "\n";
			new_room->visible = true;
			new_room->addToDisplayTree();

		}
	}

	// close doors if enemies exist

//	Tween *playerPosTween = new Tween(player);
	TweenJuggler *juggler = TweenJuggler::getInstance();
//	playerPosTween->animate(field, player->position.x, player->position.x + (((int)(endPos-startPos)>>31)^100), 100, TWEEN_LINEAR, EASE_IN);
//	juggler->add(playerPosTween);

	// no tweening until we add functionality to tween camera
	Camera *myCamera = Camera::getCamera();
	if (!zoomed_out) {
		if (current_x == boss_x && current_y == boss_y) {
			int room_size_x = 512;
			int room_size_y = 384;
			int x_adj = (boss_x - start_x) * room_size_x;
			int y_adj = (boss_y - start_y) * room_size_y;
			Player *p = Player::getPlayer();
			Camera *myCamera = Camera::getCamera();
			int c_x, c_y;
			if (p->position.x - x_adj > 0) {
				c_x = 1200 * (current_x);
			} else {
				c_x = 1200 * (current_x - 1);
			}
			if (p->position.y - y_adj > 0) {
				c_y = 900 * (current_y);
			} else {
				c_y = 900 * (current_y - 1);
			}
			myCamera->setLocation(c_x, c_y);
		}
		printf("after transition, curr x and y are %d     %d\n", current_x,
				current_y);
		Tween *camPosTween = new Tween(Camera::getCamera()->container);
		camPosTween->animate(field, -startPos, -endPos, 30, TWEEN_LINEAR,
		EASE_INOUT);
		juggler->add(camPosTween);
	}
	if (new_room) {
		changingRoom = new_room;
		if (changingRoom->room->numEnemies > 0)
			changingRoom->closeDoors();
		timer = 0;
	}

}
