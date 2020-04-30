#include "Jelly.h"
#include "DisplayObjectContainer.h"
#include <cstdlib>

using namespace std;

Jelly::Jelly(Player *player) :
		Enemy(player) {
	this->loadTexture("resources/enemies/jelly.png");
	this->id = "ENEMY_Jellyfish";
	this->scaleX *= 32. / w;
	this->scaleY *= 48. / h;
	this->xBound = 512 - (w * scaleX);
	this->yBound = 384 - (h * scaleY);
	xSpe = 2;
	ySpe = 2;
	state = 0;
}

Jelly::Jelly(Player *player, int d) :
		Enemy(player) {
	xSpe = 1;
	ySpe = 1;
	switch (d) {
	case 0: {
		this->loadTexture("./resources/art/hades/ghost.png");
		this->id = "ENEMY_Jellyfish"; //shouldn't do anything
		this->scaleX *= 1;
		this->scaleY *= 1;
		this->xp = 5;
		this->setAlpha(100);
		this->setHitbox(.1, .9, .1, .7);
		this->showHitbox = true;
		break;
	}
	case 1: {
		this->loadTexture("resources/enemies/jelly.png");
		this->id = "ENEMY_Jellyfish";
		this->scaleX *= 32. / w;
		this->scaleY *= 48. / h;
		xSpe = 3;
		ySpe = 3;
		damage = 3;
		this->xp = 10;
		health = 300;
		this->setHitbox(.1, .9, .1, .9);
		this->showHitbox = true;
		break;
	}
	case 2: {
		this->loadTexture("./resources/enemies/wasp.png");
		this->id = "ENEMY_Jellyfish"; //shouldn't do anything
		this->scaleX *= 1;
		this->scaleY *= 1;
		xSpe = 3;
		ySpe = 3;
		damage = 5;
		this->xp = 20;
		health = 400;
		//this->setAlpha(100);
		this->setHitbox(.1, .9, .2, .9);
		this->showHitbox = true;
		break;
	}
	case 3: {
		this->loadTexture("./resources/enemies/ojelly.png");
		this->id = "ENEMY_Jellyfish"; //shouldn't do anything
		this->scaleX *= 1;
		this->scaleY *= 1;
		xSpe = 4;
		ySpe = 4;
		damage = 8;
		this->xp = 50;
		health = 600;
		this->setAlpha(100);
		this->setHitbox(.1, .9, .1, .9);
		this->showHitbox = true;
		break;
	}
	default: {
		this->loadTexture("resources/enemies/jelly.png");
		this->id = "ENEMY_Jellyfish";
		this->scaleX *= 32. / w;
		this->scaleY *= 48. / h;
		xSpe = 2;
		ySpe = 2;
		damage = 3;
		health = 300;
		this->setHitbox(.1, .9, .1, .9);
		this->showHitbox = true;
	}
	}

	this->xBound = 512 - (w * scaleX);
	this->yBound = 384 - (h * scaleY);

	state = 0;
}

void Jelly::update(set<SDL_Scancode> pressedKeys) {
	Sprite::update(pressedKeys);
	if (state == 0) {
		timer++;
		if (timer >= 180) {
			state++;
		}
	} else if (state == 1) {
		timer++;
		if (timer >= 360) {
			timer = 0;
		}
	}
	// cout << position.x << ", " << position.y << endl;
	position.x += xSpe;
	position.y += ySpe;
	if (position.x <= 0 || position.x >= xBound) {
		xSpe *= -1;
	}
	if (position.y <= 0 || position.y >= yBound) {
		ySpe *= -1;
	}
}

void Jelly::draw(AffineTransform &at) {
	Enemy::draw(at);
}
