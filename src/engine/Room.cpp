#include "Room.h"

Room::Room(string scene):DisplayObjectContainer() {
	room = new Scene();
	room->loadScene(scene);
	addChild(room);
}

Room::Room(string scene, unsigned char doors){
	room = new Scene();
	// need a way to dynamically change these paths. Probably just pass them in from dungeon
	string paths[4] = {"./resources/art/hades/u_door2.png","./resources/art/hades/r_door2.png",
		"./resources/art/hades/lo_door2.png","./resources/art/hades/l_door2.png"};
	// if all rooms are the same dimensions for every dungeon this should be constant
	int coords[4][2] = {{192,0},{480,128},{192,352},{0,128}};
	SDL_Point hitboxes[4][4]=
	{
		{{0,0}, {128,0},{128,5}, {0,5} },
		{{27,0}, {32,0}, {32,128}, {27,128}},
		{{0,27}, {128,27}, {128,32}, {0,32}},
		{{0,0}, {5,0}, {5,128}, {0,128} }
	};
	int id[4] = {3,4,1,2};
	for(int i = 1, y = 0; i < 16 && y < 4; i*=2, y++){
		if(doors & i){
			Door* door = new Door("Door"+to_string(id[y]), paths[y]);
			door->moveTo(coords[y][0], coords[y][1]);
			door->setSpeed(5);
			door->setRotation(.05);
			door->setHitbox(hitboxes[y]);
			door->showHitbox = true;
			room->addChild(door);
		}
	}

	room->loadScene(scene);
	addChild(room);
}

void Room::update(set<SDL_Scancode> pressedKeys) {
	if (active||start)
		room->update(pressedKeys);
}

void Room::draw(AffineTransform &at) {
	DisplayObjectContainer::applyTransformations(at);
	if (visible)
		room->draw(at);
	DisplayObjectContainer::reverseTransformations(at);

}
