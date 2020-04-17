#include "Enemy.h"
#include "Cerb.h"
#include <cstdlib>

using namespace std;

Cerb::Cerb(Player* player) : Enemy(player){
  type = "ENEMY";
  this->id = "ENEMY_BOSS1";
  this->loadTexture("resources/enemies/CerbIdle.png");
  this->player = player;
  this->w = 50; this->h = 50;
  this->pivot.x = this->w/2;
  this->pivot.y = this->h/2;
  state = 0;
  position.x = 0;
  position.y = 0;
}

void Cerb::update(set<SDL_Scancode> pressedKeys){
  Sprite::update(pressedKeys);
  //states:
  //0 initial set up
  //1 prowling
  //2 approaching
  //3 lunge
  //4 flame attack
  //5 avoiding
  //6 dead

  //state logic
  if (health == 0){
    state = 6;
  }
  if (state == 0){
    Enemy::setPatrolRange();
  }
  else if (state == 1){
    Enemy::patrol();
  }
  else if (state == 2){
    Enemy::moveToTarget();
  }
  else if (state == 3){
    //lunge();
  }
  else if (state == 4){
    //shoot();
  }
  else if (state == 5){
    //avoid();
  }
  else if (state == 6){

  }

  //state changes
  if (state == 0){
    state = 1;
    this->targX = std::rand()%(this->maxPatX-this->minPatX) + this->minPatX;
		this->targY = std::rand()%(this->maxPatY-this->minPatY) + this->minPatY;
    this->vel = 0;
    this->maxVel = 4;
  }
  else if (state == 1){
    prowlTime++;
    int dist = std::max(std::abs(this->position.x-this->player->position.x),std::abs(this->position.y-this->player->position.y));
    if (dist < 500){ //starts approaching if player close
      state = 2;
      vel = 0;
      maxVel = 8;
      acc = .25;
      prowlTime = 0;
      targX = player->position.x;
      targY = player->position.y;
    }
    else if (prowlTime >= 180){ //ranged attack if player still far after a bit
      state = 4;
      vel = 0;
      maxVel = 0;
      acc = 0.25;
      prowlTime = 0;
    }
  }
  else if (state == 2){
    if (Enemy::isTargetReached()){
      state = 3;
      targX = player->position.x;
      targY = player->position.y;
    }
  }
}

void Cerb::draw(AffineTransform &at){
  Enemy::draw(at);
}
