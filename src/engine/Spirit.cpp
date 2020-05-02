#include "Spirit.h"
#include "DisplayObjectContainer.h"
#include "Room.h"
#include "Camera.h"
#include <cstdlib>

using namespace std;

Spirit::Spirit(Player *player) :
		Enemy(player) {
	this->loadTexture("resources/enemies/jelly.png");
	this->id = "ENEMY_Spirit";
	this->scaleX *= 32. / w;
	this->scaleY *= 48. / h;
	this->xBound = 512 - (w * scaleX);
	this->yBound = 384 - (h * scaleY);
	xSpe = 2;
	ySpe = 2;
	state = 0;
}

Spirit::Spirit(Player *player, int d) :
		Enemy(player) {
	//xSpe = 1;
	//ySpe = 1;

	switch (d) {
	case 0: {
		this->loadTexture("./resources/enemies/spirit.png");
		this->id = "ENEMY_Spirit"; //shouldn't do anything
		//this->scaleX *= 0.08;
		//this->scaleY *= 0.08;
		xSpe = 1;
		ySpe = 1;
		this->setAlpha(100);
		//this->setHitbox(.38,.58,.2,.7);
		health = 35;
		this->xp = 10;
		restTime = 2;
		//this->showHitbox = true;
		break;
	}
	case 1: {
		this->loadTexture("resources/enemies/spirit.png");
		this->id = "ENEMY_Spirit";
		//this->scaleX *= 0.08;//32./w;
		//this->scaleY *= 0.08; ///h;
		xSpe = 2;
		ySpe = 2;
		damage = 8;
		health = 200;
		this->xp = 200;
		restTime = 2;
		//	this->setHitbox(.38,.58,.2,.7);
		// this->showHitbox = true;
		break;
	}
	case 2: {
		this->loadTexture("resources/enemies/spirit.png");
		this->id = "ENEMY_Spirit";
		//this->scaleX *= 0.15;//32./w;
		//this->scaleY *= 0.15; ///h;
		cout << "spirit case 2" << endl;

		xSpe = 1;
		ySpe = 1;
		damage = 16;
		health = 800;
		this->xp = 1000;
		restTime = 0;
		//this->setHitbox(.1,.9,.1,.9);
		// this->showHitbox = true;
		break;
	}
	case 3: {
		this->loadTexture("resources/enemies/spirit.png");
		this->id = "ENEMY_Spirit";
		//this->scaleX *= 0.15;//32./w;
		//this->scaleY *= 0.15; ///h;
		xSpe = 1;
		ySpe = 1;
		damage = 32;
		health = 3000;
		this->xp = 2000;
		restTime = 0;

		//this-setHitbox(.1,.9,.1,.9);
		// this->showHitbox = true;
		break;
	}

	default: {
		this->loadTexture("resources/enemies/spirit.png");
		this->id = "ENEMY_Spirit";
		//this->scaleX *= 0.15;//32./w;
		//this->scaleY *= 0.15; ///h;
		xSpe = 2;
		ySpe = 2;
		damage = 3;
		health = 300;
		//this->setHitbox(.1,.9,.1,.9);
		// this->showHitbox = true;
		break;

	}
	}
	//this->restTime = 3;	
	this->setAlpha(100);

	this->scaleX *= 0.08;
	this->scaleY *= 0.08;
	this->setHitbox(.38, .58, .2, .7);
	this->timer = 0;
	this->xBound = 512 - (w * scaleX);
	this->yBound = 384 - (h * scaleY);

	state = 0;
}

void Spirit::update(set<SDL_Scancode> pressedKeys) {
	Sprite::update(pressedKeys);
	timer++;
	if (timer < restTime) {
		return;
	}
	timer = 0;
	/*if (state == 0) {
	 timer++;
	 if (timer >= 180) {
	 state++;
	 }
	 } else if (state == 1) {
	 timer++;
	 if (timer >= 360) {
	 timer = 0;
	 }
	 }*/
	SDL_Point charLoc = Player::getPlayer()->getPosition();
	AffineTransform *at = getGlobalTransform(Player::getPlayer());
	charLoc = at->transformPoint(0, 0);
	delete at;

	AffineTransform *at2 = getGlobalTransform(this);
	globalPos = at2->transformPoint(0, 0);
	delete at2;

	if (globalPos.x < charLoc.x) {
		position.x += xSpe;
	} else if (globalPos.x > charLoc.x) {
		position.x -= xSpe;
		if (position.x < 0) {
			position.x = 0;
		}
	}
	if (globalPos.y < charLoc.y) {
		position.y += ySpe;
	} else if (globalPos.y > charLoc.y) {
		position.y -= ySpe;
		if (position.y < 0) {
			position.y = 0;
		}
	}
	//delete charLoc;
	//nixalmighty#1230
	//position.x += xSpe;
	//position.y += ySpe;
	/*if (position.x <= 0 || position.x >= xBound) {
	 xSpe *= -1;
	 }
	 if (position.y <= 0 || position.y >= yBound) {
	 ySpe *= -1;
	 }*/
}

void Spirit::draw(AffineTransform &at) {
	Enemy::draw(at);
}
