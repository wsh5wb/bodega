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
