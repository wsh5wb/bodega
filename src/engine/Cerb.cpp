#include "Enemy.h"
#include "Cerb.h"
#include <cstdlib>

using namespace std;

Cerb::Cerb(Player* player) : Enemy(player){
  type = "ENEMY";
  this->id = "ENEMY_BOSS1";
  this->loadTexture("resources/enemies/CerbIdle.png");
  this->player = player;
  this->w = 150; this->h = 150;
  this->pivot.x = 0;//this->w/2;
  this->pivot.y = 0;//this->h/2;
  state = 0;
  position.x = 0;
  position.y = 0;
  form = 0;
}

void Cerb::update(set<SDL_Scancode> pressedKeys){
  Sprite::update(pressedKeys);

  SDL_Point charLoc = Player::getPlayer()->getPosition();
  AffineTransform* at = getGlobalTransform(Player::getPlayer());
  charLoc = at->transformPoint(0, 0);
  delete at;

  AffineTransform* at2 = getGlobalTransform(this);
  SDL_Point globalPos = at2->transformPoint(0, 0);
  delete at2;
  //states:
  //0 initial set up
  //1 prowling
  //2 approaching
  //3 lunge
  //4 flame attack
  //5 avoiding
  //6 dead

  //state logic
  //cout << "STATE = " << state << endl;

  //cout << "Cerb: " << this->position.x << ", " << this->position.y << endl;
  //cout << "Player: " << this->player->position.x << ", " << this->player->position.y << endl;

  if (health == 0){
    state = 6;
  }
  if (state == 0){
    Enemy::setPatrolRange();
  }
  else if (state == 1){
    Enemy::patrol();
    //shoot(charLoc, globalPos);
  }
  else if (state == 2){
    //Enemy::moveToTarget();
  }
  else if (state == 3){
    //lunge();
    if (globalPos.x < charLoc.x){
      position.x += 3;
    }
    else if (globalPos.x > charLoc.x){
      position.x -= 3;
    }
    if (globalPos.y < charLoc.y){
      position.y += 3;
    }
    else if (globalPos.y > charLoc.y){
      position.y -= 3;
    }
  }
  else if (state == 4){
    shoot(charLoc, globalPos);
  }
  else if (state == 5){
    Enemy::moveToTarget();
  }
  else if (state == 6){

  }

  //state changes
  //cout << "Cerb State: " << state << endl;
  //cout << "Cerb Pos: " << globalPos.x << ", " << globalPos.y << "\n";
  if (state == 0){
    state = 1;
    this->targX = std::rand()%(this->maxPatX-this->minPatX) + this->minPatX;
		this->targY = std::rand()%(this->maxPatY-this->minPatY) + this->minPatY;
    this->vel = 0;
    this->maxVel = 4;
  }
  else if (state == 1){
    //cout << "In state 1" << endl;
    prowlTime++;
    int dist = std::max(std::abs(charLoc.x-globalPos.x),std::abs(charLoc.y-globalPos.y));
    if (dist < 300){ //starts approaching if player close
      state = 2;
      vel = 0;
      maxVel = 8;
      acc = .25;
      prowlTime = 0;
    }
    else if (prowlTime >= 180){ //ranged attack if player still far after a bit
      state = 4;
      vel = 0;
      maxVel = 0;
      acc = 0.25;
      prowlTime = 0;
    }
    else{
      shoot(charLoc, globalPos);
    }
  }
  else if (state == 2){
    prowlTime++;
    if (globalPos.x < charLoc.x){
      position.x += 2;
    }
    else if (globalPos.x > charLoc.x){
      position.x -= 2;
    }
    if (globalPos.y < charLoc.y){
      position.y += 2;
    }
    else if (globalPos.y > charLoc.y){
      position.y -= 2;
    }
    if (prowlTime > 120){
      state = 3;
      prowlTime = 0;
    }
  }
  else if (state == 3){;
    lungeTime++;
    if (lungeTime > 10){
      restCount++;
      //runs away on being hit while vulnerable, to a spot at least 50 away from player
      if (wasHit()){
        if (std::rand()%2 == 0)
        this->targX = 50 + std::rand()%(500) + this->position.x;
        else
        this->targX = -50 + -1*std::rand()%(500) + this->position.x;
        if (std::rand()%2 == 0)
        this->targY = 50 + std::rand()%(500) + this->position.y;
        else
        this->targY = -50 -1*std::rand()%(500) + this->position.y;
        state = 5;
      }
      //when below half health, less time vulnerable
      if (restCount >= 75 || (health < 250 && restCount >= 30)){
        cout << maxPatX << endl;
        restCount = 0;
        state = 1;
      }
    }
    else{
      shoot(charLoc, globalPos);
    }
  }
  else if (state == 4){
    //state = 1;
    restCount++;
    if (wasHit()){
      if (std::rand()%2 == 0)
      this->targX = 50 + std::rand()%(500) + player->position.x;
      else
      this->targX = -50 + -1*std::rand()%(500) + player->position.x;
      if (std::rand()%2 == 0)
      this->targY = 50 + std::rand()%(500) + player->position.y;
      else
      this->targY = -50 + -1*std::rand()%(500) + player->position.y;
      state = 5;
    }
    if (restCount >= 55 || (health < 250 && restCount >= 25)){
      state = 1;
    }
  }
  else if (state == 5){
    //Run away until target reached or hits the edge of the room
    if (Enemy::isTargetReached() || atWall()){
      state = 1;
    }
  }
  else if (state == 6){
    //TODO: add death animation
  }
}

void Cerb::draw(AffineTransform &at){
  Enemy::draw(at);
}

void Cerb::shoot(SDL_Point charLoc, SDL_Point globalPos){
  //TODO: Give Cerberus projectiles to use
  int projX = 0;
  int projY = 0;
  //float angle = atan2(globalPos.y - charLoc.y, globalPos.x - charLoc.x)*180/PI;
  //cout << "Cerb Angle: " << angle << endl;
  int diffX = globalPos.x - charLoc.x;
  int diffY = globalPos.y - charLoc.y;
  if(globalPos.x < charLoc.x && abs(diffX) > 30){
    projX = projectileSpeed;
  }
  //else if (globalPos.x < charLoc.x && abs(diffX) < 30 && abs(diffX) > 10){
  //  projX = projectileSpeed/2;
  //}
  else if(globalPos.x > charLoc.x && abs(diffX) > 30){
    projX = -projectileSpeed;//*xRate;
  }
  //else if (globalPos.x > charLoc.x && abs(diffX) < 30 && abs(diffX) > 10){
  //  projX = -projectileSpeed/2;
  //}
  if(globalPos.y < charLoc.y && abs(diffY) > 30){
    projY = projectileSpeed;
  }
  //else if (globalPos.y < charLoc.y && abs(diffY) < 30 && abs(diffY) > 10){
  //  projY = projectileSpeed/2;
  //}
  else if(globalPos.y > charLoc.y && abs(diffY) > 30){
    projY = -projectileSpeed;
  }
  //else if (globalPos.y < charLoc.y && abs(diffY) < 30 && abs(diffY) > 10){
  //  projY = -projectileSpeed/2;
  //}


  if(projX != 0 && projY != 0){
    projX = projX/1.4142;
    projY = projY/1.4142;
  }
  int midX, midY;
  if (form == 0){
    midX = this->position.x + (dstrect.w)/3;
    midY = this->position.y + (dstrect.h)/3;
  }
  else if (form == 1){
    midX = this->position.x + 115;
    midY = this->position.y + 60;
  }
  else if (form == 2){
    midX = this->position.x + 15;
    midY = this->position.y + 15;
  }
  else{
    midX = this->position.x + 10;
    midY = this->position.y + 10;
  }
  //cout << "Getting to before adding the projectile" << endl;
  Projectile * p = new Projectile("resources/Projectiles/spikedball.png", midX, midY,projX,projY,1500,0.15,0.15,projectileDamage);
  //p->showHitbox = true;
  ((DisplayObjectContainer*)(this->parent))->addChild(p);
  DTEvent e("OBJ_ADD", &Game::eventHandler, p);
  Game::eventHandler.dispatchEvent(&e);
  //cout << "Getting to the end of Shoot" << endl;
}

bool Cerb::wasHit(){
  //TODO: return true if collision was with Player's attack
  return false;
}

bool Cerb::atWall(){
  //TODO: return true if touching wall or other solid non-player object
  return false;
}

void Cerb::addProjectile(int speedX, int speedY, int timeout, double scaleX, double scaleY){
	//string path = "./resources/PlayerSprites/fireball.png";
	//int midX = this->position.x + (w*scaleX)/3;
	//int midY = this->position.y + (w*scaleX)/3;
	//printf("Adding new projectile\n");
	////Projectile * p = new Projectile(path,midX,midY,speedX,speedY,timeout,scaleX,scaleY);
	//// projectiles.push_back(p);
	//((DisplayObjectContainer*)this->parent)->addChild(p);
	//DTEvent e("OBJ_ADD", &Game::eventHandler, p);
	//Game::eventHandler.dispatchEvent(&e);
}
