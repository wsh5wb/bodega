#include "Enemy.h"
#include "Skel.h"
#include <cstdlib>

using namespace std;

Skel::Skel(Player* player) : Enemy(player){
  type = "ENEMY";
  id = "ENEMY_SKEL";
  this->loadTexture("resources/enemies/SkelDead.png");
  this->player = player;
  w = 40; h = 60;
  pivot.x = w/2;
  pivot.y = h/2;
  state = 0;
  position.x = 0;
  position.y = 0;
}

void Skel::update(set<SDL_Scancode> pressedKeys){
  Sprite::update(pressedKeys);
  //states:
  //0 hiding
  //1 standing, idle
  //2 approaching
  //3 attacking
  //4 dying
  if (health == 0){
    state = 4;
  }
  if (state == 0){
    hide();
  }
  else if (state == 1){
    if (this->imgPath != "resources/enemies/SkelIdle.png"){
      int oldX = position.x;
      int oldY = position.y;
      this->loadTexture("resources/enemies/SkelIdle.png");
      position.x = oldX;
      position.y = oldY;
      w = 40;
      h = 60;
    }
  }
  else if (state == 2){
    Enemy::moveToTarget();
  }
  else if (state == 3){
    axeAttack();
  }
  else if (state == 4){

  }
  //state changes
  if (state == 0){
    int dist = std::max(std::abs(this->position.x-this->player->position.x),std::abs(this->position.y-this->player->position.y));
    if (dist < 250){
      state = 1;
    }
  }
  else if (state == 1){
    idleTime++;
    int dist = std::max(std::abs(this->position.x-this->player->position.x),std::abs(this->position.y-this->player->position.y));
    if (dist < 300){
      state = 2;
      vel = 0;
      maxVel = 3;
      acc = .25;
      targX = player->position.x;
      targY = player->position.y;
      idleTime = 0;
    }
    else if (idleTime > 120){ //if idle for too long, hides
      state = 0;
      idleTime = 0;
    }
  }
  else if (state == 2){
    chaseTime++;
    int dist = std::max(std::abs(this->position.x-this->player->position.x),std::abs(this->position.y-this->player->position.y));
    targX = player->position.x;
    targY = player->position.y;
    if (chaseTime > 180 && dist > 50){
      chaseTime = 0;
      state = 1;
    }
    else if (Enemy::isTargetReached() || dist < 10){
      chaseTime = 0;
      state = 3;
    }
  }
  else if (state == 3){
    attackTime++;
    if (attackTime > 20){
      state = 1;
    }
  }
  else if (state == 4){
    //TODO: death animation, spawn bone pile
  }
}

void Skel::draw(AffineTransform &at){
  Enemy::draw(at);
}

void Skel::hide(){
  int oldX = position.x;
  int oldY = position.y;
  if (this->imgPath != "resources/enemies/SkelDead.png"){
    this->loadTexture("resources/enemies/SkelDead.png");
    position.x = oldX;
    position.y = oldY;
    w = 40;
    h = 20;
  }
}

void Skel::axeAttack(){
  //TODO: add attack animation/hitbox
}
