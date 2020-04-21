#include "Enemy.h"
#include "DisplayObjectContainer.h"
#include <cstdlib>

using namespace std;

//Here, "Player" is the player character
Enemy::Enemy(Player* player) : Sprite("ENEMY", "resources/enemies/enemyFloating_1.png"){
	this->type = "ENEMY";
	this->player = player;
	this->w = 42; this->h = 40;
	this->pivot.x = this->w/2;
	this->pivot.y = this->h/2;
	this->state = 0;
	this->position.x=0;
	this->position.y=0;
	this->rotVel=0;
	this->rotAcc=0.007;
	this->maxRotVel=0.35;
}

void Enemy::update(set<SDL_Scancode> pressedKeys){
	Sprite::update(pressedKeys);


	//enemy is dead so clean it up
	//if(this->health == 0){
	//	//this->clean = true; //scene will clean it up
	//}
	////do the actual cleaning if necessary
	//if(this->clean){
	//	this->removeThis();
	//	delete this;
	//}

	//everything else controlled by state machine
	//state 0 = one time state to kick things off
	//state 1 = patrolling
	//state 2 = readying a charge
	//state 3 = charging
	//state 4 = post-charge movement
	//state 5 = stunned

	if(this->state == 0){
		setPatrolRange();
	}
	else if(this->state == 1){
		patrol();
	}
	else if(this->state == 2){
		prepareCharge();
	}
	else if(this->state == 3){
		// this->targX = player->position.x;
		// this->targY = player->position.y;
		charge();
	}
	else if(this->state == 4){
		moveToTarget();
	}
	else if(this->state == 5){
		this->rotation -= 1;
	}

	//state transitions
	if(this->state == 0){
		this->state = 1;
		this->targX = std::rand()%(this->maxPatX-this->minPatX) + this->minPatX;
		this->targY = std::rand()%(this->maxPatY-this->minPatY) + this->minPatY;
		this->vel = 0;
		this->maxVel = 4;
	}
	else if(this->state == 1){
		//if player is close, start to prepare charge
		int dist = std::max(std::abs(this->position.x-this->player->position.x),std::abs(this->position.y-this->player->position.y));
		//cout<<dist<<endl;
		if(dist<500){
			this->state = 2;
			this->vel = 0;
			this->maxVel = 12;
			this->acc = 0.5;
			this->rotVel = 0;
			this->rotAcc = 0.007;
			this->maxRotVel = 0.35;
		}
	}
	else if(this->state == 2){
		if(std::abs(this->rotVel) - this->maxRotVel > -0.0001){
			this->state = 3;
			this->targX = this->player->position.x;
			this->targY = this->player->position.y;
		}
	}
	else if(this->state == 3){
		//cout<<pivot.x<<endl;
		if(isTargetReached()){
			this->state = 4;
			this->rotation = 0;
			this->rotVel = 0;
			this->targX = this->position.x;
			this->targY = this->position.y - 350;
		}
	}
	else if(this->state == 4){
		if(isTargetReached()){
			this->state = 1;
			this->setPatrolRange();
		}
	}
	if(this->shield == 0){
		this->state = 5;
	}
	//cout<<this->state<<endl;
}

void Enemy::onMeleeStrike(){
	this->shield -= 10;
	if(this->shield < 0) this->shield = 0;
}

void Enemy::changeHealth(int amount){
	health += amount;
	if(health <= 0){
		((DisplayObjectContainer *)this->parent)->removeImmediateChild(this);
	}
}

//void Enemy::onEssenceStrike(Weapon* w){
//
//	if(this->shield <= 0) this->health -= w->damage;
//	if(this->health < 0) this->health = 0;
//}

//void Enemy::onCollision(DisplayObject* other){
//	if(other->type == "Weapon"){
//		if(controls::pressSpecial())
//			onEssenceStrike((Weapon*)other);
//	}
//	else if(other->type == "Blast"){
//		if(controls::pressAttack())
//			onMeleeStrike();
//	}
//}

void Enemy::draw(AffineTransform &at){
	Sprite::draw(at);
	//this->drawHitbox();
}

//void Enemy::save(ofstream &out){
//	Sprite::save(out);
//	//TODO: ADD THIS TO SAVE ENEMY DATA
//}

void Enemy::charge(){
	this->rotation += this->rotVel;
	moveToTarget();
}

void Enemy::prepareCharge(){
	this->rotVel = std::min(this->rotVel+this->rotAcc, this->maxRotVel);
	this->rotation += this->rotVel;
}

void Enemy::setPatrolRange(){
	this->minPatX = this->position.x-120;
	this->maxPatX = this->position.x+120;
	this->minPatY = this->position.y-120;
	this->maxPatY = this->position.y+120;
}

void Enemy::patrol(){
	//if close to target, set a new one

	if(isTargetReached() && pauseCount == 119){
		this->targX = std::rand()%(this->maxPatX-this->minPatX) + this->minPatX;
		this->targY = std::rand()%(this->maxPatY-this->minPatY) + this->minPatY;
		this->vel = 0;
		this->maxVel = 4;
		this->pauseCount = 0;
	}

	if(pauseCount < 119){
		pauseCount = (pauseCount+1) % 120;
	}
	else{
		moveToTarget();
	}
}

void Enemy::moveToTarget(){

	//increase velocity by accel
	this->vel = std::min(this->vel+this->acc, this->maxVel);

	//use unit vector to determine percent that goes into x and y
	double theta = std::atan2(std::abs(this->targY - this->position.y),std::abs(this->targX - this->position.x));
	double xComp = this->vel*std::cos(theta);
	double yComp = this->vel*std::sin(theta);
	if(this->targX - this->position.x < 0) xComp *= -1;
	if(this->targY - this->position.y < 0) yComp *= -1;

	this->position.x += xComp;
	this->position.y += yComp;
}

bool Enemy::isTargetReached(){
	return std::abs(this->position.x-this->targX) <= 6 && std::abs(this->position.y-this->targY) <= 6;
}
