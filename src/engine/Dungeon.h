#ifndef DUNGEON_H
#define DUNGEON_H

#include "DisplayObjectContainer.h"
#include "Room.h"
#include "MazeGenerator.h"
#include "Camera.h"
#include "EventListener.h"
#include "Sound.h"

#define ROOM_START_DELAY 30 //number of frames before room starts being active after player enters
#define PORTAL_DIST 2

using namespace std;

class Dungeon : public DisplayObjectContainer, EventListener{

public:
	Dungeon();
	~Dungeon();
	void cleanMatrix(int** m);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	virtual void generate();//sets up layout, reads in scenes, generates rooms
	virtual void generateNoBoss();//sets up layout, reads in scenes, generates rooms (doesn't have boss room)
	virtual void handleEvent(Event* e);

	int ** layout; //2d int array representing dungeon structure where -1 is empty and each other int is index into scenes for that room's corrosponding scene
	vector<string> scenes;//list of paths to scenes representing rooms in dungeon
	int start_x, start_y, current_x, current_y, boss_x = -1, boss_y = -1;
	bool zoomed_out = true;
	bool DEBUG_CHANGE_ROOM = false;
	int * basic_rooms;
	int basic_rooms_size = 0;
	int portal_index = -1;
	int dungeonType = 0;
	int timer = 0;
	Room* changingRoom = NULL;
	int oldSpeed = 0;

private:
	int portalDist(int x1, int x2, int y1, int y2);
	SDL_Point boss_locations[4];
	bool isBossRoom(int x, int y);
	void transitionRoom(string type);
};

#endif
