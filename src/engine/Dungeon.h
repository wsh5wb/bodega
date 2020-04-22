#ifndef DUNGEON_H
#define DUNGEON_H

#include "DisplayObjectContainer.h"
#include "Room.h"
#include "MazeGenerator.h"
#include "Camera.h"
#include "EventListener.h"

#define NUM_DUNGEONS	2
#define HADES		 	0
#define OCEAN			1

using namespace std;

class Dungeon : public DisplayObjectContainer, EventListener{

public:

	~Dungeon();
	void cleanMatrix(int** m);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	virtual void generate();//sets up layout, reads in scenes, generates rooms
	virtual void handleEvent(Event* e);

	int ** layout; //2d int array representing dungeon structure where -1 is empty and each other int is index into scenes for that room's corrosponding scene
	vector<string> scenes;//list of paths to scenes representing rooms in dungeon
	int start_x, start_y, current_x, current_y;
	bool zoomed_out = true;
	bool DEBUG_CHANGE_ROOM = false;
	int * basic_rooms;
	int basic_rooms_size = 0;

private:
	void transitionRoom(string type);
};

class DungeonManager : EventListener{
public:
	virtual void handleEvent(Event* e){
		if(e->getType() == "CHANGE_DUNGEON"){
			printf("Changing dungeon\n");
			curr_dungeon = (curr_dungeon+1)%NUM_DUNGEONS;
		}
	}

	unsigned char curr_dungeon = 0;
	// probably put num dungeons in define statement somewhere
	Dungeon* dungeons[NUM_DUNGEONS];
};

#endif
