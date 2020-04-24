#ifndef ROOM_H
#define ROOM_H

#include "DisplayObjectContainer.h"
#include "Scene.h"

using namespace std;

class Room: public DisplayObjectContainer{

public:

	Room(string scene);
	Room(string scene, unsigned char doors);
	Room(string scene, unsigned char doors, int d);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	void addToDisplayTree();
	void removeFromDisplayTree();

	bool active = false;
	bool start = false;
	bool visible = false; //draws scene if visible, updates and draws if active
	Scene *room = NULL; //scene that room draws
	
	int dungeonType = 0;

	void openDoors();
	void closeDoors();

private:
	void generateDoors(unsigned char doors);
	void generateWalls();
};

#endif
