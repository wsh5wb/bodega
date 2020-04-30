#include "Portal.h"
#include "Game.h"

using namespace std;

Portal::Portal() : AnimatedSprite("PORTAL"){
	printf("MAKING PORTAL\n");
	this->addAnimation("resources/art/spritesheets/portal.png",
			"resources/art/spritesheets/portal.xml", "Idle", 1, 60, true);
	this->play("Idle");

	Game::eventHandler.addEventListener((EventListener*) this, "BOSS_KILLED");
	// Game::cs->watchForCollisions("PLAYER", "PORTAL");
}

Portal::~Portal(){
	// Game::cs->ignoreCollisions("PLAYER", "PORTAL");
	Game::eventHandler.removeEventListener((EventListener*) this, "BOSS_KILLED");
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

void Portal::handleEvent(Event* e){
	if(e->getType() == "BOSS_KILLED"){
		this->makeVisible();
		Game::cs->watchForCollisions("PLAYER", "PORTAL");
	}
}