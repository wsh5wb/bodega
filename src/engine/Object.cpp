#include "Object.h"
#include "DTEvent.h"
#include "Game.h"
#include <iostream>

using namespace std;

Object::Object() :
		DisplayObject() {
	boundLowX = boundLowY = 0;
	boundHighX = boundHighY = 1;
}

Object::~Object() {
}

void Object::hitbox(){
	setHitbox(boundLowX, boundHighX, boundLowY, boundHighY);
}

void Object::update(set<SDL_Scancode> pressedKeys) {
	DisplayObject::update(pressedKeys);
}

void Object::draw(AffineTransform &at) {
	DisplayObject::draw(at);
}

void Object::saveSelf(vector<string> &objects, vector<string> &dependencies) {
	string desc;
	stringstream sstm;
	int px0 = pivot.x, px1 = position.x, py0 = pivot.y, py1 = position.y;
	sstm << "9 " << id << " " << imgPath << " " << red << " " << green << " "
			<< blue << " " << std::boolalpha << vis << " " << std::boolalpha
			<< isRGB << " " << w << " " << h << " " << speed << " " << scaleX
			<< " " << scaleY << " " << rotation << " " << rotationAmount << " "
			<< alpha << " " << px0 << " " << py0 << " " << px1 << " " << py1
			<< " " << boundLowX << " " << boundHighX << " " << boundLowY << " "
			<< boundHighY << "\n";
	desc = sstm.str();
	objects.push_back(desc);

}
