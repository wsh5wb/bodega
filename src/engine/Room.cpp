#include "Room.h"
#include "Door.h"

Room::Room(string scene):DisplayObjectContainer() {
	room = new Scene();
	room->loadScene(scene);
	addChild(room);
}

Room::Room(string scene, unsigned char doors){
	room = new Scene();
	generateDoors(doors);
	room->loadScene(scene);
	generateWalls();
	addChild(room);
}

void Room::addToDisplayTree(){
	//addChild(room);
}

void Room::removeFromDisplayTree(){
	//removeImmediateChild(room);
}

void Room::generateDoors(unsigned char doors){
	// need a way to dynamically change these paths. Probably just pass them in from dungeon
	string paths[4] = {"./resources/art/hades/u_door2.png","./resources/art/hades/r_door2.png",
		"./resources/art/hades/lo_door2.png","./resources/art/hades/l_door2.png"};
	// if all rooms are the same dimensions for every dungeon this should be constant
	int coords[4][2] = {{192,0},{480,128},{192,352},{0,128}};
//	double hitboxes[4][4] =
//	{
//		{{51,0}, {77,0},{77,10}, {51,10} },
//		{{22,51}, {32,51}, {32,77}, {22,77} },
//		{{51,22}, {77,22}, {77,32}, {51,32} },
//		{{0,51}, {10,51}, {10,77}, {0,77} }
//	};
	 double hitboxes[4][4] =
	 {
	 	{.4,.6,0,.3125},
	 	{.6875,1,.23,.37 },
	 	{ .4,.6,.6875,1},
	 	{ 0,.3125,.23,.37}
	 };

	int id[4] = {3,4,1,2};
	for(int i = 1, y = 0; i < 16 && y < 4; i*=2, y++){
		if(doors & i){
			Door* door = new Door("Door"+to_string(id[y]), paths[y]);
			door->moveTo(coords[y][0], coords[y][1]);
			door->setSpeed(5);
			door->setRotation(.05);
			//door->setHitbox(hitboxes[y]);
			door->setHitbox(hitboxes[y][0],hitboxes[y][1],hitboxes[y][2],hitboxes[y][3]);
			door->showHitbox = true;
			door->room = this;
			room->addChild(door);
		}
	}
}

void Room::generateWalls(){
	int w = room->w, h = room->h;
	// ordered NESW
	SDL_Point position[4] = {{0,0},{w-3,0},{0,h-3}};
	int dimensions[2][2] = {{w,3},{3,h}};
	for(int i =0; i < 4; i++){
		DisplayObject* wall = new DisplayObject();
		wall->id = "OBSTACLE_WALL" + to_string(i+1);
		//%3 because north and west walls share same top-left
		wall->moveTo(position[i%3].x, position[i%3].y);
		wall->w = dimensions[i%2][0];
		wall->h = dimensions[i%2][1];
		wall->setHitbox(0,1);
		//wall->showHitbox = true;
		// printf("Adding wall%d at (%d,%d)\n", i+1,position[i%3].x,position[i%3].y);
		room->addChild(wall);
	}
}

void Room::update(set<SDL_Scancode> pressedKeys) {

	if (active||start){
		room->update(pressedKeys);
	}
}

void Room::draw(AffineTransform &at) {
	DisplayObjectContainer::applyTransformations(at);
	if (visible)
		room->draw(at);
	DisplayObjectContainer::reverseTransformations(at);

}

void Room::openDoors(){

	Game::cs->watchForCollisions("DOOR", "PLAYER");
	for(DisplayObject* child : room->children){
		if(child->id.substr(0,4) == "Door"){
			printf("opening %s\n", child->id.c_str());
			child->makeVisible();
		}
	}
	// if(activeRoom->room->numEnemies == 0)
	// 	printf("No Enemies\n");
	// else
	// 	printf("Num enemies = %d\n", activeRoom->room->numEnemies--);

}

void Room::closeDoors(){
	Game::cs->ignoreCollisions("DOOR", "PLAYER");
	for(DisplayObject* child : room->children){
		if(child->id.substr(0,4) == "Door"){
			printf("closing %s\n", child->id.c_str());
			child->makeInvisible();
		}
	}
}
