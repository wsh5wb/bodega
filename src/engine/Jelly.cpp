#include "Jelly.h"
#include "DisplayObjectContainer.h"
#include <cstdlib>

using namespace std;

Jelly::Jelly(Player *player) :
		Enemy(player) {
	this->loadTexture("resources/enemies/jelly.png");
	this->id = "ENEMY_Jellyfish";
	this->scaleX *= 32./w;
	this->scaleY *= 48./h;
	this->xBound = 512 - (w * scaleX);
	this->yBound = 384 - (h * scaleY);
	xSpe = rand()%5-2;
	ySpe = rand()%5-2;
	state = 0;
}

Jelly::Jelly(Player *player, int d) :
		Enemy(player) {
	xSpe = rand()%7-3;
	ySpe = rand()%7-3;
	if(xSpe==ySpe){
		xSpe=rand()%7-3;
		ySpe=rand()%7-3;
	}
	if(xSpe==0){xSpe=rand()%15-7;}
	if(ySpe==0){ySpe=rand()%15-7;}
	timer+=rand()%200;
	switch (d) {
		case 0: {
			this->loadTexture("./resources/art/hades/ghost.png");
			this->id = "ENEMY_Jellyfish"; //shouldn't do anything
			this->scaleX *= 1;
			this->scaleY *= 1;
			this->setAlpha(100);
			this->setHitbox(.1,.9,.1,.7);
			this->showHitbox = true;
			break;
		}
		default: {
			this->loadTexture("resources/enemies/jelly.png");
			this->id = "ENEMY_Jellyfish";
			this->scaleX *= 32./w;
			this->scaleY *= 48./h;
			xSpe = rand()%5-2;
			ySpe = rand()%5-2;
			damage = 3;
			health = 300;
			this->setHitbox(.1,.9,.1,.9);
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
		if (timer >= 250) {
			state++;
			xSpe=rand()%3-1;
			ySpe=rand()%3-1;
		}
	} else if (state == 1) {
		timer+=1;
		if (timer >= 330) {
			timer = 0;
			state=0;
			while(abs(xSpe)+abs(ySpe)<3){
				xSpe=rand()%9-4;
				ySpe=rand()%9-4;
			}
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
