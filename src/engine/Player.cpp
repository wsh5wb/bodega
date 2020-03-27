#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
//#include "Controls.h"

using namespace std;


Player::Player() : AnimatedSprite("PLAYER_YOU"){

	this->type = "Player";

	this->position.x = 55;
	this->position.y = 200;
	this->w = 416;
	this->h = 454;
	this->scaleX = 0.15;
	this->scaleY = 0.15;
	this->pivot.x = 0;//this->w / 2;
	this->pivot.y = 0;//this->h / 2;
	this->addAnimation("resources/PlayerSprites/idleSprite.png", "resources/PlayerSprites/idleSheet.xml", "Idle", 1, 60, true);
	this->addAnimation("resources/PlayerSprites/runSprite.png", "resources/PlayerSprites/runSheet.xml", "Run", 1, 60, true);
	this->addAnimation("resources/PlayerSprites/jumpsprites.png", "resources/PlayerSprites/jumpSheet.xml", "Jump", 1, 60, false);
	this->play("Idle");
	//cout << "Getting here." << endl;
}

//Called automatically by collision system when something collides with the player
//our job is to simply react to that collision.
void Player::onCollision(DisplayObject* other){
	if(other->type == "Platform"){
		//Game::instance->collisionSystem.resolveCollision(this, other, this->position.x - oldX, this->position.y - oldY);
		_yVel = 0;
		_standing=true;
	}
	else if(other->type == "Enemy"){
		if(!this->iFrames){
			//this->onEnemyCollision((Enemy*)other);
		}
	}

}


void Player::update(set<SDL_Scancode> pressedKeys){
	AnimatedSprite::update(pressedKeys);
	oldY = this->position.y;
	oldX = this->position.x;

	//Movement arrow keys
	//Controls is a class we wrote that just checks the SDL Scancode values and game controller values in one check
	bool idle = true;
	for (auto k : pressedKeys)
		if(k == SDL_SCANCODE_RIGHT){
			this->position.x += 4;
			//this->flipH = false;
			if(this->currAnimation != "Run"){
				this->play("Run");
			}
			this->flip = SDL_FLIP_NONE;
			idle = false;
		}
		else if(k == SDL_SCANCODE_LEFT){
			this->position.x -= 4;
			//this->flipH = true;
			if(this->currAnimation != "Run"){
				this->play("Run");
			}
			this->flip = SDL_FLIP_HORIZONTAL;
			idle = false;
		}
		else if (k== SDL_SCANCODE_UP){
			this->position.y -= 4;
			if (this->currAnimation != "Run"){
				this->play("Run");
			}
			idle = false;
		}
		else if (k == SDL_SCANCODE_DOWN){
			this->position.y += 4;
			if (this->currAnimation != "Run"){
				this->play("Run");
			}
			idle = false;
		}


	//play idle animation if player is just standing still on ground
	if(this->currAnimation == "Run" && idle){
		this->play("Idle");
	}


	/* handle iFrames if player was hit by enemy recently */
	if(this->iFrames){
		//this->visible = this->iFrameCount%2 == 0;
		this->iFrameCount++;
		if(this->iFrameCount == this->numIFrames){
			this->iFrames = false;
			//this->visible = true;
		}
	}

	/* Calculate fall velocity */
	_yAccCount++;
	if(_yAccCount == _yAcc){
		_yAccCount=0;
		_yVel++;
		if(_yVel > _maxFall) _yVel = _maxFall;
	}

	/* Jumping */
	//if(_standing && controls::pressJump()){
	//	this->_yVel = _jumpVel;
	//	_standing = false;
	//	this->play("Jump");
	//}

	/* Actual falling depending on falling versus whether a jump occurred */
	//this->position.y += _yVel;
}

//void Player::onEnemyCollision(Enemy* enemy){
//	this->health -= enemy->damage;
//	this->initIFrames(120);
//}

void Player::initIFrames(int numFrames){
	this->iFrameCount = 0;
	this->numIFrames = numFrames;
	this->iFrames = true;
}

void Player::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}
