#include "Jelly.h"
#include "DisplayObjectContainer.h"
#include <cstdlib>
#include "Projectile.h"
#include "DTEvent.h"

using namespace std;

Jelly::Jelly(Player *player) :
		Enemy(player) {
	this->loadTexture("resources/enemies/jelly.png");
	this->id = "ENEMY_Jellyfish";
	this->scaleX *= 32. / w;
	this->scaleY *= 48. / h;
	this->xBound = 512 - (w * scaleX);
	this->yBound = 384 - (h * scaleY);
	xSpe = rand() % 7 - 3;
	ySpe = rand() % 7 - 3;
	state = 0;
	type = 0;
}

Jelly::Jelly(Player *player, int d) :
		Enemy(player) {
	do {
		xSpe = rand() % 5 - 2;
		ySpe = rand() % 5 - 2;
	} while ((xSpe == 0 && ySpe == 0));
	timer += 20 * rand() % 15;
	type = d;
	this->path = "resources/Projectiles/Stinger2.png";
	switch (d) {
	case 0: {
		this->loadTexture("./resources/art/hades/ghost.png");
		this->id = "ENEMY_Jellyfish"; //shouldn't do anything
		this->scaleX *= 1;
		this->scaleY *= 1;
		this->xp = 5;
		health = 20;
		this->setAlpha(100);
		this->setHitbox(.1, .9, .1, .7);
		// this->showHitbox = true;
		break;
	}
	case 1: {
		this->loadTexture("resources/enemies/jelly.png");
		this->id = "ENEMY_Jellyfish";
		this->scaleX *= 32. / w;
		this->scaleY *= 48. / h;
		do {
			xSpe = rand() % 7 - 3;
			ySpe = rand() % 7 - 3;
		} while ((xSpe == 0 && ySpe == 0));
		damage = 3;
		this->xp = 100;
		health = 75;
		this->setHitbox(.1, .9, .1, .9);
		// this->showHitbox = true;
		break;
	}
	case 2: {
		this->loadTexture("./resources/enemies/wasp.png");
		this->id = "ENEMY_Jellyfish"; //shouldn't do anything
		this->path = "resources/Projectiles/Stinger2.png";
		this->scaleX *= 1;
		this->scaleY *= 1;
		do {
			xSpe = rand() % 7 - 3;
			ySpe = rand() % 7 - 3;
		} while ((xSpe == 0 && ySpe == 0));
		damage = 5;
		this->xp = 500;
		health = 600;
		maxCoolDown = 200;
		//this->setAlpha(100);
		this->projectileDamage = 5;
		this->projectileSpeed = 4;
		this->setHitbox(.1, .9, .2, .9);
		// this->showHitbox = true;
		break;
	}
	case 3: {
		this->loadTexture("./resources/enemies/ojelly.png");
		this->id = "ENEMY_Jellyfish"; //shouldn't do anything
		this->path = "resources/Projectiles/Stinger2.png";
		this->scaleX *= 1;
		this->scaleY *= 1;
		do {
			xSpe = rand() % 9 - 4;
			ySpe = rand() % 9 - 4;
		} while ((xSpe == 0 && ySpe == 0));
		damage = 8;
		this->xp = 2500;
		health = 1200;
		maxCoolDown = 150;
		this->projectileDamage = 8;
		this->projectileSpeed = 6;
		this->setAlpha(100);
		this->setHitbox(.1, .9, .1, .9);
		// this->showHitbox = true;
		break;
	}
	default: {
		this->loadTexture("resources/enemies/jelly.png");
		this->id = "ENEMY_Jellyfish";
		this->scaleX *= 32. / w;
		this->scaleY *= 48. / h;
		xSpe = rand() % 7 - 3;
		ySpe = rand() % 7 - 3;
		damage = 16;
		health = 300;
		this->setHitbox(.1, .9, .1, .9);
		// this->showHitbox = true;
	}
	}

	this->xBound = 512 - (w * scaleX);
	this->yBound = 384 - (h * scaleY);
	nextShot = (rand() % (1 + maxCoolDown)) - 1;

	state = 0;
}

void Jelly::update(set<SDL_Scancode> pressedKeys) {
	Sprite::update(pressedKeys);
	restTimer++;
	if (restTimer < restTime) {
		return;
	}
	restTimer = 0;
	timer++;
	/*if (timer >= 360) {
	 timer = 0;
	 }*/
	if (type > 1) {
		if (timer > nextShot) {
			SDL_Point charLoc = Player::getPlayer()->getPosition();
			AffineTransform *at = getGlobalTransform(Player::getPlayer());
			charLoc = at->transformPoint(0, 0);
			delete at;

			AffineTransform *at2 = getGlobalTransform(this);
			SDL_Point globalPos = at2->transformPoint(0, 0);
			delete at2;

			int projX = 0;
			int projY = 0;
			if (globalPos.x < charLoc.x) {
				projX = projectileSpeed;
			} else if (globalPos.x > charLoc.x) {
				projX = -projectileSpeed;
			}
			if (globalPos.y < charLoc.y) {
				projY = projectileSpeed;
			} else if (globalPos.y > charLoc.y) {
				projY = -projectileSpeed;
			}

			if (projX != 0 && projY != 0) {
				projX = projX / 1.4142;
				projY = projY / 1.4142;
			}

			int midX = this->position.x + (dstrect.w) / 3;
			int midY = this->position.y + (dstrect.h) / 3;
			Projectile *p = new Projectile(path, midX, midY, projX, projY, 1500,
					0.15, 0.15, projectileDamage);
			//p->showHitbox = true;
			((DisplayObjectContainer*) (this->parent))->addChild(p);
			DTEvent e("OBJ_ADD", &Game::eventHandler, p);
			Game::eventHandler.dispatchEvent(&e);
			nextShot = timer + (rand() % maxCoolDown);
		}
	}
	position.x += xSpe;
	position.y += ySpe;
	if (position.x <= 0 || position.x >= xBound || position.y <= 0
			|| position.y >= yBound) {
		if (position.x <= 0 || position.x >= xBound) {
			xSpe *= -1;
		} else {
			ySpe *= -1;
		}
		if (position.x < 0) {
			position.x = 1;
		} else {
			if (position.x > xBound) {
				position.x = xBound - 1;
			}
		} //xSpe=-rand()%5;}
		if (position.y < 0) {
			position.y = 1;
		} else {
			if (position.y > yBound) {
				position.y = yBound - 1;
			}
		} //ySpe=-rand()%5;}
	}
	if(position.x>5 && position.x <xBound-5 && position.y>5 && position.y<yBound-5){
	if (state == 0) {
		timer++;
		if (timer % 340 >= 250) {
			state++;
			xSpe = rand() % 3 - 1;
			ySpe = rand() % 3 - 1;
		}
	} else if (state == 1) {
		timer += 1;
		if (timer % 340 >= 330) {
			//timer = 0;
			state = 0;
			timer += 10 + rand() % 20;
			while (abs(xSpe) + abs(ySpe) < 4 || abs(xSpe)+abs(ySpe)>11) {
				xSpe = rand() % (9 + timer / 3000) - 5;
				ySpe = rand() % (9 + timer / 3000) - 5;
			}
		}
	} else {
		timer = 0;
		state = 0;
	}}
	if (timer < 0) {
		timer = 0;
	}

	// cout << position.x << ", " << position.y << endl;
	//position.x += xSpe;
	//position.y += ySpe;
	/*if (position.x <= 0 || position.x >= xBound) {
	 xSpe *= -1;
	 }
	 if (position.y <= 0 || position.y >= yBound) {
	 ySpe *= -1;
	 }*/
}

void Jelly::draw(AffineTransform &at) {
	Enemy::draw(at);
}
