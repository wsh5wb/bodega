#include "Portal.h"

using namespace std;

Portal::Portal() : AnimatedSprite("PORTAL"){
	printf("MAKING PORTAL\n");
	this->addAnimation("resources/art/spritesheets/portal.png",
			"resources/art/spritesheets/portal.xml", "Idle", 1, 60, true);
	this->play("Idle");
}

Portal::~Portal(){

}

void Portal::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

void Portal::update(set<SDL_Scancode> pressedKeys){
	AnimatedSprite::update(pressedKeys);
}

void Portal::saveSelf(vector<string> &objects, vector<string> &dependencies){
	AnimatedSprite::saveSelf(objects, dependencies);
}