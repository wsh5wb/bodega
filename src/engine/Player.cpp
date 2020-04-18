#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "DTEvent.h"

//#include "Controls.h"

using namespace std;
Player *Player::player = 0;
Player::Player() :
		AnimatedSprite("PLAYER_YOU") {

	this->type = "Player";

	this->position.x = 55;
	this->position.y = 200;
	this->w = 416;
	this->h = 454;
	this->scaleX = 0.15;
	this->scaleY = 0.15;

	this->pivot.x = 0; //this->w / 2;
	this->pivot.y = 0; //this->h / 2;
	this->addAnimation("resources/PlayerSprites/idleSprite.png",
			"resources/PlayerSprites/idleSheet.xml", "Idle", 1, 60, true);
	this->addAnimation("resources/PlayerSprites/runSprite.png",
			"resources/PlayerSprites/runSheet.xml", "Run", 1, 60, true);
	this->addAnimation("resources/PlayerSprites/jumpsprites.png",
			"resources/PlayerSprites/jumpSheet.xml", "Jump", 1, 60, false);
		this->play("Idle");
	//for tweening Demo
		// this->alpha = 30;
		// TweenJuggler * juggle = TweenJuggler::getInstance();
		// Tween * alpha_tween = new Tween(this);
		// alpha_tween->animate(TWEEN_ALPHA, this->alpha, 230, 500, TWEEN_LINEAR, EASE_IN);
		// juggle->add(alpha_tween);
	//for Tweening Demo
	//cout << "Getting here." << endl;
}

Player::~Player(){
	// for(vector<Projectile*>::iterator it = projectiles.begin(); it != projectiles.end();it++){
	// 	delete *it;
	// }projectiles.clear();
}

Player* Player::getPlayer() {
	if (player == 0) {
		player = new Player();
	}
	return player;
}

//Called automatically by collision system when something collides with the player
//our job is to simply react to that collision.
void Player::onCollision(DisplayObject *other) {
	if (other->type == "Platform") {
		//Game::instance->collisionSystem.resolveCollision(this, other, this->position.x - oldX, this->position.y - oldY);
		_yVel = 0;
		_standing = true;
	} else if (other->type == "Enemy") {
		if (!this->iFrames) {
			//this->onEnemyCollision((Enemy*)other);
		}
	}else if (other->type == "door") {
		cerr << "colliding with " << other->id <<"\n";
	}

}

void Player::renderHPBar(int x, int y, int w, int h, float PercentLost, SDL_Color FGColor, SDL_Color BGColor) {
		if (PercentLost < 0.0){
			PercentLost = 0.0;
		}else if (PercentLost > 1.0){
			PercentLost = 1.0;
		}
   SDL_Color old;
   SDL_GetRenderDrawColor(Game::renderer, &old.r, &old.g, &old.g, &old.a);
   SDL_Rect bgrect = { x, y, w, h };
   SDL_SetRenderDrawColor(Game::renderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
   SDL_RenderFillRect(Game::renderer, &bgrect);
   SDL_SetRenderDrawColor(Game::renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
   int pw = (int)((float)w * PercentLost);
   int px = x + (w - pw);
   SDL_Rect fgrect = { px, y, pw, h };
   SDL_RenderFillRect(Game::renderer, &fgrect);
   SDL_SetRenderDrawColor(Game::renderer, old.r, old.g, old.b, old.a);
}

float Player::percentOfHealthLost(){
		float d = (float(this->maxHealth - this->health)/ float(this->maxHealth));
		//printf("Max Health: %x, health %x, percentLoss %9.6f \n", this->maxHealth, this->health, d);
		return d;
}

void Player::changeHealth(int value){
		this->health += value;
}

void Player::toggleHealthDisplay(){
		this->displayHealth = !(this->displayHealth);
}

void Player::addProjectile(int speedX, int speedY, int timeout, double scaleX, double scaleY){
	string path = "./resources/PlayerSprites/fireball.png";
	int midX = this->position.x + 20;
	int midY = this->position.y + 20;
	Projectile * p = new Projectile(path,midX,midY,speedX,speedY,timeout,scaleX,scaleY);
	// projectiles.push_back(p);
	((DisplayObjectContainer*)this->parent)->addChild(p);
}

void Player::update(set<SDL_Scancode> pressedKeys) {
	AnimatedSprite::update(pressedKeys);
	oldY = this->position.y;
	oldX = this->position.x;

	//if(find(pressedKeys.begin(),pressedKeys.end())
	//Movement arrow keys
	//Controls is a class we wrote that just checks the SDL Scancode values and game controller values in one check
	int xMov = 0, yMov = 0;
	bool idle = true;
	for (auto k : pressedKeys){
		if (k == SDL_SCANCODE_RIGHT) {
			this->position.x += 4;
			this->deltaX += 4;
			//this->flipH = false;
			if (this->currAnimation != "Run") {
				this->play("Run");
			}
			this->flip = SDL_FLIP_NONE;
			idle = false;
		} else if (k == SDL_SCANCODE_LEFT) {
			this->position.x -= 4;
			this->deltaX += -4;
			//this->flipH = true;
			if (this->currAnimation != "Run") {
				this->play("Run");
			}
			this->flip = SDL_FLIP_HORIZONTAL;
			idle = false;
		} else if (k == SDL_SCANCODE_UP) {
			this->position.y -= 4;
			this->deltaY += -4;
			if (this->currAnimation != "Run") {
				this->play("Run");
			}
			idle = false;
		} else if (k == SDL_SCANCODE_DOWN) {
			this->position.y += 4;
			this->deltaY += 4;
			if (this->currAnimation != "Run") {
				this->play("Run");
			}
			idle = false;
		}

		//for shooting projectiles
		if(k == SDL_SCANCODE_A){
			xMov = -6;
		}if(k == SDL_SCANCODE_D){
			xMov = 6;
		}if(k == SDL_SCANCODE_W){
			yMov = -6;
		}if(k == SDL_SCANCODE_S){
			yMov = 6;
		}
		//for tweening Demo
		else if (k == SDL_SCANCODE_T){
			TweenJuggler * juggle = TweenJuggler::getInstance();
			Tween * position_tween = new Tween(this);
			position_tween->animate(TWEEN_POSITION_X, oldX, oldX + 200, 200, TWEEN_QUADRATIC, EASE_IN);
			juggle->add(position_tween);
		}
		else if (k == SDL_SCANCODE_R){
			TweenJuggler * juggle = TweenJuggler::getInstance();
			Tween * position_tween = new Tween(this);
			position_tween->animate(TWEEN_POSITION_X, oldX, oldX - 200, 200, TWEEN_SINE, EASE_OUT);
			juggle->add(position_tween);
		}
		else if (k == SDL_SCANCODE_SEMICOLON){
			changeHealth(-20);
		}
		else if (k == SDL_SCANCODE_APOSTROPHE){
			changeHealth(20);
		}
		/*else if (k == SDL_SCANCODE_COMMA){
			toggleHealthDisplay();
		*/
		/*else if (k == SDL_SCANCODE_SPACE){
			if (this->currAnimation != "Dead"){
				this->play("Dead");
			}
		}*/
	}
	//play idle animation if player is just standing still on ground
	if (this->currAnimation == "Run" && idle) {
		this->play("Idle");
	}

	/* handle iFrames if player was hit by enemy recently */
	if (this->iFrames) {
		//this->visible = this->iFrameCount%2 == 0;
		this->iFrameCount++;
		if (this->iFrameCount == this->numIFrames) {
			this->iFrames = false;
			//this->visible = true;
		}
	}

	/* Calculate fall velocity */
	_yAccCount++;
	if (_yAccCount == _yAcc) {
		_yAccCount = 0;
		_yVel++;
		if (_yVel > _maxFall)
			_yVel = _maxFall;
	}

	// // Update projectiles
	// for(vector<Projectile*>::iterator it = projectiles.begin(); it != projectiles.end();){
	// 	Projectile * p = *it;
	// 	if((((std::clock() - p->start ) / (double) CLOCKS_PER_SEC)*1000) > p->timeout){
	// 		it = projectiles.erase(it);

	// 		((DisplayObjectContainer*)this->parent)->removeImmediateChild(*it);
	// 		// delete p;
	// 	}else{
	// 		// p->update(pressedKeys);
	// 		it++;
	// 	}

	// }

	if(xMov != 0 || yMov != 0){
		if((((std::clock() - lastFired) / (double) CLOCKS_PER_SEC)*1000) > 150){
			addProjectile(xMov,yMov,1000,0.3,0.3);
			lastFired = std::clock();
		}
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

void Player::initIFrames(int numFrames) {
	this->iFrameCount = 0;
	this->numIFrames = numFrames;
	this->iFrames = true;
}

void Player::draw(AffineTransform &at) {
	AnimatedSprite::draw(at);
	renderHPBar(20, 20, 200, 25, percentOfHealthLost(), colorSDL(128, 0, 0, 220), colorSDL(34, 139, 34, 220));
	// for(Projectile* p : projectiles){
	// 	p->draw(at);
	// }

}

void Player::saveSelf(vector<string> &objects, vector<string> &dependencies) {
	string desc;
	stringstream sstm;

	int px1 = position.x, py1 = position.y;
	sstm << "7 " << px1 << " " << py1 << "\n";
	desc = sstm.str();
	objects.push_back(desc);
	for (DisplayObject *child : children) {
		string dep = id + " " + child->id + "\n";
		dependencies.push_back(dep);
		child->saveSelf(objects, dependencies);
	}
}
