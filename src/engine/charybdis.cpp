#include "Enemy.h"
#include "charybdis.h"
#include <cstdlib>

using namespace std;

charybdis::charybdis(Player* player) : Enemy(player){
  type = "ENEMY";
  this->id = "ENEMY_BOSS1";
  this->loadTexture("resources/enemies/hydra.png");
  this->player = player;
  this->w = 150; this->h = 150;
  this->pivot.x = 0;//this->w/2;
  this->pivot.y = 0;//this->h/2;
  state = 0;
  position.x = 0;
  position.y = 0;
  xSpe = rand()%5-2;
	ySpe = rand()%5-2;
}

charybdis::charybdis(Player *player, int d) :
		Enemy(player) {
	xSpe = rand() % 7 - 3;
	ySpe = rand() % 7 - 3;
	//timer += 20 * rand() % 15;
	type = d;
	//this->path = "resources/Projectiles/Stinger2.png";
	switch (d) {
	case 2: {
		this->loadTexture("./resources/enemies/wasp.png");
		this->id = "ENEMY_Jellyfish"; //shouldn't do anything
		//this->path = "resources/Projectiles/Stinger2.png";
		this->scaleX *= 1;
		this->scaleY *= 1;
		xSpe = rand() % 7 - 3;
		ySpe = rand() % 7 - 3;
		damage = 5;
		this->xp = 500;
		health = 300;
		//maxCoolDown = 200;
		//this->setAlpha(100);
		//this->projectileDamage = 5;
		//this->projectileSpeed = 4;
		this->setHitbox(.1, .9, .2, .9);
		// this->showHitbox = true;
		break;
	}
	case 3: {
		this->loadTexture("./resources/enemies/ojelly.png");
		this->id = "ENEMY_Jellyfish"; //shouldn't do anything
		this->scaleX *= 1;
		this->scaleY *= 1;
		xSpe = rand() % 11 - 5;
		ySpe = rand() % 11 - 5;
		damage = 8;
		this->xp = 2500;
		health = 500;
		this->setAlpha(100);
		this->setHitbox(.1, .9, .1, .9);
		// this->showHitbox = true;
		break;
	}
	default: {
		this->loadTexture("resources/enemies/charyb.png");
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

}

void charybdis::update(set<SDL_Scancode> pressedKeys){
  Sprite::update(pressedKeys);

  // SDL_Point charLoc = Player::getPlayer()->getPosition();
  // AffineTransform* at = getGlobalTransform(Player::getPlayer());
  // charLoc = at->transformPoint(0, 0);
  // delete at;
  //
  // AffineTransform* at2 = getGlobalTransform(this);
  // SDL_Point globalPos = at2->transformPoint(0, 0);
  // delete at2;

  position.x += xSpe;
  position.y += ySpe;
  if (position.x <= 25 || position.x >= 900) {
    xSpe *= -1;
  }
  if (position.y <= 25 || position.y >= 600) {
    ySpe *= -1;
}
}

void charybdis::draw(AffineTransform &at){
  Enemy::draw(at);
}
