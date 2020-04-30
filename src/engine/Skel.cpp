#include "Enemy.h"
#include "Skel.h"
#include <cstdlib>

using namespace std;

Skel::Skel(Player *player) :
		Enemy(player) {
	type = "ENEMY";
	id = "ENEMY_SKEL";
	this->loadTexture("resources/enemies/SkelDead.png");
	this->player = player;
	w = 40;
	h = 60;
	pivot.x = 0; // w/2;
	pivot.y = 0; //h/2;
	state = 5;
	position.x = 0;
	position.y = 0;
	this->setAlpha(15);
}

void Skel::update(set<SDL_Scancode> pressedKeys) {
	Sprite::update(pressedKeys);
	restTimer++;
	if (restTimer < restTime) {
		return;
	}
	restTimer = 0;
	//states:
	//0 hiding
	//1 standing, idle
	//2 approaching
	//3 attacking
	//4 dying
	if (health == 0) {
		state = 4;
	}
	SDL_Point charloc = getGlobalTransform(Player::getPlayer())->transformPoint(
			0, 0);
	SDL_Point globalpos = getGlobalTransform(this)->transformPoint(0, 0);
	if (state == 5) {
		position.x+=rand()%50;
		position.y+=rand()%75-50;
		if (std::max(abs(globalpos.x - charloc.x), abs(globalpos.y - charloc.y))
				> 250) {
			state = 0;
		}
	}
	if (state == 0) {
		this->setAlpha(15);
		// hide();
	} else if (state == 1) {
		if (this->imgPath != "resources/enemies/SkelIdle.png") {
			int oldX = position.x;
			int oldY = position.y;
			this->loadTexture("resources/enemies/SkelIdle.png");
			position.x = oldX;
			position.y = oldY;
			w = 40;
			h = 60;
		}
	} else if (state == 2) {
		Enemy::moveToTarget();
	} else if (state == 3) {
		axeAttack();
	} else if (state == 4) {

	}
	//state changes
	//SDL_Point charLoc = Player::getPlayer()->getPosition();
	//AffineTransform* at = getGlobalTransform(Player::getPlayer());
	//SDL_Point charloc = getGlobalTransform(Player::getPlayer())->transformPoint(0,0);
	//SDL_Point globalpos = getGlobalTransform(this)->transformPoint(0,0);
	//cout<<charloc.x<<" "<<globalpos.x<<endl;
	//delete charloc;
	//delete globalpos;
	if (state == 0) {
		int dist = std::max(std::abs(globalpos.x - charloc.x),
				std::abs(globalpos.y - charloc.y));
		if (dist < 250) {
			state = 1;
			this->setAlpha(100);
		}
	} else if (state == 1) {
		idleTime++;
		int dist = std::max(std::abs(globalpos.x - charloc.x),
				std::abs(globalpos.y - charloc.y));
		if (dist < 300) {
			state = 2;
			vel = 0;
			maxVel = 3;
			acc = .25;
			targX = charloc.x;
			targY = charloc.y;
			idleTime = 0;
		} else if (idleTime > 120) { //if idle for too long, hides
			state = 0;
			idleTime = 0;
		}
	} else if (state == 2) {
		chaseTime++;
		int dist = std::max(std::abs(globalpos.x - charloc.x),
				std::abs(globalpos.y - charloc.y));
		targX = charloc.x;
		targY = charloc.y;
		if (chaseTime > 180 && dist > 50) {
			chaseTime = 0;
			state = 1;
		} else if (Enemy::isTargetReached() || dist < 10) {
			chaseTime = 0;
			state = 3;
		}
	} else if (state == 3) {
		attackTime++;
		if (attackTime > 20) {
			state = 1;
		}
	} else if (state == 4) {
		//TODO: death animation, spawn bone pile
	}
	//SDL_Point targets = getGlobalTransform(this)->reverseTransform(targX,targY);
	targX = targX - globalpos.x + this->position.x;
	targY = targY - globalpos.y + this->position.y;
}

void Skel::draw(AffineTransform &at) {
	Enemy::draw(at);
}

void Skel::hide() {
	int oldX = position.x;
	int oldY = position.y;
	if (this->imgPath != "resources/enemies/SkelDead.png") {
		this->loadTexture("resources/enemies/SkelDead.png");
		position.x = oldX;
		position.y = oldY;
		w = 40;
		h = 20;
	}
}

void Skel::axeAttack() {
	//TODO: add attack animation/hitbox
}
