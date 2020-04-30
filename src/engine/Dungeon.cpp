#include "Dungeon.h"
#include <SDL2/SDL.h>
#include "TweenJuggler.h"
#include "Camera.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "HadesDungeon.h"
#include "Portal.h"
#include "charybdis.h"

using namespace std;

Dungeon::Dungeon() {
	Game::eventHandler.addEventListener((EventListener*) this, "DUNG_TRANS_U");
	Game::eventHandler.addEventListener((EventListener*) this, "DUNG_TRANS_D");
	Game::eventHandler.addEventListener((EventListener*) this, "DUNG_TRANS_R");
	Game::eventHandler.addEventListener((EventListener*) this, "DUNG_TRANS_L");
	Game::eventHandler.addEventListener((EventListener*) this, "ENEMY_KILLED");
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
			printf("Camera being set to (0,0)\n");
			myCamera->setLocation(0, 0);
			myCamera->setZoom(500 / GRID_SIZE, 500 / GRID_SIZE);
			Game::instance->paused = true;
			Game::instance->mapMode = true;

		}
	} else {
		if (zoomed_out) {
			zoomed_out = false;
			printf("Camera being set to (%x,%x)\n", current_y, current_x);
			Camera *myCamera = Camera::getCamera();
			myCamera->setLocation(1200 * current_x, 900 * current_y);
			myCamera->setZoom(500, 500);
		}
	}

	//camera for being in dungeon
	if (!zoomed_out && (current_x == boss_x || current_x == boss_x - 1)
			&& (current_y == boss_y || current_y == boss_y - 1)) {
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
			c_x = 1200 * boss_x + 2.34375 * (p->position.x - x_adj) - 600;
		} else if (p->position.x - x_adj > (-room_size_x / 2)) {
			c_x = 1200 * (boss_x);
		} else {
			c_x = 1200 * (boss_x - 1);
		}
		if (p->position.y - y_adj < (room_size_y / 2)
				&& p->position.y - y_adj > (-room_size_y / 2)) {
			c_y = 900 * boss_y + 2.34375 * (p->position.y - y_adj) - 450;
		} else if (p->position.y - y_adj > (-room_size_y / 2)) {
			c_y = 900 * (boss_y);
		} else {
			c_y = 900 * (boss_y - 1);
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
				if (old_room)
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
			cerr << "current room: (" << current_x << ", " << current_y
					<< ")\n";
			cerr << "boss room: (" << boss_x << ", " << boss_y << ")\n";
			cerr << "player x: " << p->position.x;
			cerr << "\nplayer y: " << p->position.y << "\n\n";
			break;
		}

		}
	}
	if (changingRoom) {
		Player *p = Player::getPlayer();
		if (timer <= ROOM_START_DELAY) {
			timer++;

		} else {
			zoomed_out = true;
			changingRoom->active = true;
			changingRoom = NULL;
			timer = 0;
			p->modifySpeed(oldSpeed);
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
	bool seenBoss = false;
	int bossRoomsCount = 0;
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
				string s;
				if (ind == BOSS_ROOM - 1) {
					printf("Boss room being processed\n");
					boss_locations[bossRoomsCount] = { j, i };
					if (!seenBoss) {
						seenBoss = true;
						boss_y = i;
						boss_x = j;
					}
					s = this->scenes.at(
							this->scenes.size() - 1 - bossRoomsCount);
				} else
					s = this->scenes.at(ind);
				Room *temp = new Room(s, doors, dungeonType);
				temp->id = id + to_string(i) + "-" + to_string(j);
				temp->moveTo(1200 * j, 900 * i);
				//temp->xLoc = j; temp->yLoc = i;

				if (ind == BOSS_ROOM - 1) {
					if (bossRoomsCount == 0) {
						temp->removeWall(NORTH);
						temp->removeWall(WEST);
					} else if (bossRoomsCount == 1) {
						temp->removeWall(NORTH);
						temp->removeWall(EAST);
					} else if (bossRoomsCount == 2) {
						temp->removeWall(SOUTH);
						temp->removeWall(WEST);
					} else if (bossRoomsCount == 3) {
						temp->removeWall(SOUTH);
						temp->removeWall(EAST);
						DisplayObject *portal = new Portal();
						portal->makeInvisible();
						Game::cs->ignoreCollisions("PLAYER", "PORTAL");
						// portal->scale(.5);
						portal->moveTo(512, 384);
						portal->translate(-portal->w / 8, -portal->h / 8);
						portal->setHitbox(.1, .9);
						temp->room->addChild(portal);
						Cerb *c = new Cerb(Player::getPlayer());
						c->originX = 512;
						c->originY = 384;
						charybdis *whirl = new charybdis(Player::getPlayer());
						//c->showHitbox = true;
						if (dungeonType == 1){
							c->loadTexture("resources/enemies/scylla.png");
							c->scaleX *= 0.35;
							c->scaleY *= 0.35;
							whirl->loadTexture("resources/enemies/hydra.png");
							whirl->health = 5000;
							c->health = 7500;
							c->form = 1;

						}
						else if (dungeonType == 2){
							c->loadTexture("resources/enemies/hydra.png");
							c->scaleX *= 1.2;
							c->scaleY *= 1.2;
							c->health = 10000;
							c->form = 2;
						}
						else if (dungeonType == 3){
							c->loadTexture("resources/enemies/Pose.png");
							c->health = 20000;
							c->form = 3;
							//Skel *s1 = new Skel(Player::getPlayer());
							//Skel *s2 = new Skel(Player::getPlayer());
							//s2->moveTo(490, 384);
							//s1->health = 5000;
							//s1->moveTo(534, 384);
							//s2->health = 5000;
							//temp->room->addChild(s1);
							//temp->room->addChild(s2);
						}
						c->moveTo(512, 384);
						whirl->moveTo(50,50);
						temp->room->addChild(c);
						temp->room->addChild(whirl);
						temp->active = true;
					}
					bossRoomsCount++;
				}

				if (start_x == j && start_y == i) {
					printf("Setting start room to active\n");
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

void Dungeon::generateNoBoss() {

	Game::cs->watchForCollisions("PLAYER", "DOOR");
	MazeGenerator M;
	cerr << "here0\n";
	layout = (int**) (M.getLayoutNoBoss());
	srand (time(NULL));int
	portal = -1;
	int count = 0;
	for (int i = GRID_SIZE; i--; i += 0) {
		for (int j = GRID_SIZE; j--;) {
			if (layout[i][j] == START_ROOM) {
				start_x = current_x = j;
				start_y = current_y = i;
			}
			layout[i][j] -= 1;
		}
	}
	bool portal_set = (portal_index == -1);
	while (!portal_set) {
		portal = rand() % (NUM_ROOMS - 1);
		count = 0;
		for (int i = GRID_SIZE; i--; i += 0) {
			for (int j = GRID_SIZE; j--;) {
				if (!(layout[i][j]) && basic_rooms_size > 0) {
					if (portal != -1 && (portal == count)) {
						if(portalDist(i,start_y,j,start_x)>PORTAL_DIST){
							layout[i][j] = portal_index;
							portal_set = true;
						}
					}
				}
				count++;
			}
		}
	}
	for (int i = GRID_SIZE; i--; i += 0) {
		for (int j = GRID_SIZE; j--;) {
			if (!(layout[i][j]) && basic_rooms_size > 0) {
				int ind = rand() % basic_rooms_size;
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
				if (ind == BOSS_ROOM - 1)
					ind = 0;
				string s = this->scenes.at(ind);
				Room *temp = new Room(s, doors, dungeonType);
				temp->id = id + to_string(i) + "-" + to_string(j);
				temp->moveTo(1200 * j, 900 * i);
				//temp->xLoc = j; temp->yLoc = i;

				if (start_x == j && start_y == i) {
					printf("Setting start room to active\n");
					temp->active = true;
					temp->start = true;
					temp->visible = true;
					start_room = temp;
					// DisplayObject *portal = new Portal();
					// portal->scale(.25);
					// portal->moveTo(512, 384);
					// portal->translate(-portal->w / 8, -portal->h / 8);
					// portal->setHitbox(.1, .9);
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
	}

}

bool Dungeon::isBossRoom(int x, int y) {
	for (SDL_Point loc : boss_locations) {
		if (loc.x == x && loc.y == y) {
			printf("in boss room!\n");
			return true;
		}
	}
	return false;
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

	TweenJuggler *juggler = TweenJuggler::getInstance();

	// no tweening until we add functionality to tween camera
	Camera *myCamera = Camera::getCamera();
	if ((current_x == boss_x || current_x == boss_x - 1)
			&& (current_y == boss_y || current_y == boss_y - 1)) {
		//current_x = boss_x;
		//current_y = boss_y;

	}
	if (!zoomed_out) {
		if ((current_x == boss_x || current_x == boss_x - 1)
				&& (current_y == boss_y || current_y == boss_y - 1)) {
			Room *br0 = (Room*) DisplayObjectContainer::getChild(
					id + to_string(boss_y) + "-" + to_string(boss_x));
			Room *br1 = (Room*) DisplayObjectContainer::getChild(
					id + to_string(boss_y - 1) + "-" + to_string(boss_x));
			Room *br2 = (Room*) DisplayObjectContainer::getChild(
					id + to_string(boss_y) + "-" + to_string(boss_x - 1));
			Room *br3 = (Room*) DisplayObjectContainer::getChild(
					id + to_string(boss_y - 1) + "-" + to_string(boss_x - 1));
			if (br0)
				br0->visible = true;
			if (br1)
				br1->visible = true;
			if (br2)
				br2->visible = true;
			if (br3)
				br3->visible = true;

			int room_size_x = 512;
			int room_size_y = 384;
			int x_adj = (boss_x - start_x) * room_size_x;
			int y_adj = (boss_y - start_y) * room_size_y;
			Player *p = Player::getPlayer();
			Camera *myCamera = Camera::getCamera();
			int c_x, c_y;
			if (p->position.x - x_adj > 0) {
				c_x = 1200 * (boss_x);
			} else {
				c_x = 1200 * (boss_x - 1);
			}
			if (p->position.y - y_adj > 0) {
				c_y = 900 * (boss_y);
			} else {
				c_y = 900 * (boss_y - 1);
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
	oldSpeed = player->getSpeed();
	player->modifySpeed(-oldSpeed);
	if (new_room) {
		changingRoom = new_room;
		if (changingRoom->room->numEnemies > 0)
			changingRoom->closeDoors();
		timer = 0;
	}

}

int Dungeon::portalDist(int x1, int x2, int y1, int y2){
	return abs(x1-x2)+abs(y1-y2);
}
