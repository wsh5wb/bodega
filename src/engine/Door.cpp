#include "Door.h"
#include "DTEvent.h"
#include "Game.h"
#include <iostream>

using namespace std;

Door::Door() : DisplayObject(){
	this->addEventListener((EventListener*) &Game::cs, "OBJ_ADD");
	this->addEventListener((EventListener*) &Game::cs, "OBJ_RM");
}

Door::Door(string id, string filepath) : DisplayObject(id,filepath){
	this->addEventListener((EventListener*) &Game::cs, "OBJ_ADD");
	this->addEventListener((EventListener*) &Game::cs, "OBJ_RM");
}

Door::Door(string id, string filepath, bool particle) : DisplayObject(id,filepath,particle){
	if(particle) {return;}
	this->addEventListener((EventListener*) &Game::cs, "OBJ_ADD");
	this->addEventListener((EventListener*) &Game::cs, "OBJ_RM");
}

Door::Door(string id, int red, int green, int blue) : DisplayObject(id,red,green,blue){
	this->addEventListener((EventListener*) &Game::cs, "OBJ_ADD");
	this->addEventListener((EventListener*) &Game::cs, "OBJ_RM");
}

Door::~Door(){
}



void Door::update(set<SDL_Scancode> pressedKeys){
	DisplayObject::update(pressedKeys);
}

void Door::draw(AffineTransform &at){
	DisplayObject::draw(at);
}

void Door::saveSelf(vector<string> &objects, vector<string> &dependencies) {
	string desc;
	stringstream sstm;
	int px0 = pivot.x, px1 = position.x, py0 = pivot.y, py1 = position.y;
	sstm << "8 " << id << " " << imgPath << " " << red << " " << green << " "
			<< blue << " " << std::boolalpha << vis << " " << std::boolalpha
			<< isRGB << " " << w << " " << h << " " << speed << " " << scaleX
			<< " " << scaleY << " " << rotation << " " << rotationAmount << " "
			<< alpha << " " << px0 << " " << py0 << " " << px1 << " " << py1
			<< "\n";
	desc = sstm.str();
	objects.push_back(desc);

}
