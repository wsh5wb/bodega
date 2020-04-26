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
	chat_box = new TextBox("There exists a fault in the totality of man that leads me ton believe in his effervesent knowledge of all things on a much deeper plane of existence give me all that you can possibly ever believe or understand");
	this->addChild(chat_box);
	chat_box->addMessagetoDisplay("OH BTW, I had more to say please please please get over the limit for sixty characters.");
	chat_box->addMessagetoDisplay("OH BTW, I had more to say please please please get over the limit for sixty characters.");
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
		printf("Making new player!\n");
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

void Player::renderXPBar(int x, int y, int w, int h, float PercentXP, SDL_Color FGColor, SDL_Color BGColor) {
	if (PercentXP < 0.0){
		PercentXP = 0.0;
	}else if (PercentXP > 1.0){
		PercentXP = 1.0;
	}
   SDL_Color old;
   SDL_GetRenderDrawColor(Game::renderer, &old.r, &old.g, &old.g, &old.a);
   SDL_Rect bgrect = { x, y, w, h };
   SDL_SetRenderDrawColor(Game::renderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
   SDL_RenderFillRect(Game::renderer, &bgrect);
   SDL_SetRenderDrawColor(Game::renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
   int pw = (int)((float)w * PercentXP);
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

float Player::percentOfXP(){
	if(level == maxLevel){ return 0.0;}
	//float d = (float(this->xpChart[level-1] - this->xp)/ float(this->xpChart[level-1]));
	float d = (float(this->xpNeeded - this->xp)/ float(this->xpNeeded));
	//printf("Max Health: %x, health %x, percentLoss %9.6f \n", this->maxHealth, this->health, d);
	return d;
}

bool Player::changeHealth(int value){
	this->health += value;
	if(health > maxHealth){
		health = maxHealth;
	}
	if(health <= 0){
		health = maxHealth;
		Event e("PLAYER_KILLED", &Game::eventHandler);
		Game::eventHandler.dispatchEvent(&e);
		Event e2("STATS_CHANGED", &Game::eventHandler);
		Game::eventHandler.dispatchEvent(&e2);
		return true;
	}
	Event e("STATS_CHANGED", &Game::eventHandler);
	Game::eventHandler.dispatchEvent(&e);
	return false;
}

void Player::changeMaxHealth(int value){
	maxHealth += value;
	health += value;
	Event e("STATS_CHANGED", &Game::eventHandler);
	Game::eventHandler.dispatchEvent(&e);
}

bool Player::checkLevelUp(){
	if(level == maxLevel){
		return false;
	}//return xp >= xpChart[level-1];
	return xp >= xpNeeded;
}

void Player::changeXP(int value){
	this->xp += value;
	while(checkLevelUp()){
		//xp -= xpChart[level-1];
		xp -= xpNeeded;
		xpNeeded *= xpScale;
		levelUp();
	}

}

int Player::getHealth(){
	return this->health;
}
int Player::getMaxHealth(){
	return this->maxHealth;
}
double Player::getSpeed(){
	return this->speed;
}
double Player::getDamage(){
	return this->damage;
}
double Player::getAttackSpeed(){
	return this->attackSpeed;
}

int Player::getLevel(){
	return this->level;
}
// Can maybe do stuff at special levels like increase speed of projectiles or amount of health or something
void Player::levelUp(){
	level++;
	cout << "You leveled up!" << endl;
	damage += 10;
	health += 10;
	maxHealth += 10;
	attackSpeed += .2;
	Event e("STATS_CHANGED", &Game::eventHandler);
	Game::eventHandler.dispatchEvent(&e);
}

void Player::modifySpeed(int value){
	runSpeed += value;
	Event e("STATS_CHANGED", &Game::eventHandler);
	Game::eventHandler.dispatchEvent(&e);
}

void Player::changeDamage(int value){
	damage += value;
	Event e("STATS_CHANGED", &Game::eventHandler);
	Game::eventHandler.dispatchEvent(&e);
}

void Player::changeAttackSpeed(double value){
	attackSpeed += value;
	Event e("STATS_CHANGED", &Game::eventHandler);
	Game::eventHandler.dispatchEvent(&e);
}

void Player::toggleHealthDisplay(){
	this->displayHealth = !(this->displayHealth);
}

void Player::addProjectile(int speedX, int speedY, int timeout, double scaleX, double scaleY){
	int midX, midY;
	switch(this->direction){
		case 1:{
			//left
			midX = this->position.x + (dstrect.w)/3;
		  midY = this->position.y + (dstrect.h)/3;
			break;
		}case 2:{
			//right
			midX = this->position.x + (dstrect.w)/6;
			midY = this->position.y + (dstrect.h)/6;
			break;
		}case 3:{
			//up
			midX = this->position.x + (dstrect.w)/6;
		 	midY = this->position.y + (dstrect.h)/3;
			break;
		}case 4:{
			//down
			midX = this->position.x + (dstrect.w)/3;
			midY = this->position.y + (dstrect.h)/6;
			break;
		}default:{
			printf("Error reached with %x \n", this->direction);
			cerr << "ERROR: Direction Parameter Not Recognized!\n";
			break;
		}
	}
	//printf("Adding new projectile\n");
	Projectile * p = new Projectile(current_ball_type, midX, midY,speedX,speedY,timeout,scaleX,scaleY);
	// projectiles.push_back(p);
	((DisplayObjectContainer*)this->parent)->addChild(p);
	DTEvent e("OBJ_ADD", &Game::eventHandler, p);
	Game::eventHandler.dispatchEvent(&e);
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
		if (k == SDL_SCANCODE_D) {
			this->position.x += runSpeed;
			this->deltaX += runSpeed;
			//this->flipH = false;
			if (this->currAnimation != "Run") {
				this->play("Run");
			}
			this->flip = SDL_FLIP_NONE;
			idle = false;
		} else if (k == SDL_SCANCODE_A) {
			this->position.x -= runSpeed;
			this->deltaX += -runSpeed;
			//this->flipH = true;
			if (this->currAnimation != "Run") {
				this->play("Run");
			}
			this->flip = SDL_FLIP_HORIZONTAL;
			idle = false;
		} else if (k == SDL_SCANCODE_W) {
			this->position.y -= runSpeed;
			this->deltaY += -runSpeed;
			if (this->currAnimation != "Run") {
				this->play("Run");
			}
			idle = false;
		} else if (k == SDL_SCANCODE_S) {
			this->position.y += runSpeed;
			this->deltaY += runSpeed;
			if (this->currAnimation != "Run") {
				this->play("Run");
			}
			idle = false;
		} else if (k == SDL_SCANCODE_1){
			this->current_ball_type = 1;
		}	else if (k == SDL_SCANCODE_2){
			this->current_ball_type = 2;
		} else if (k == SDL_SCANCODE_3){
			this->current_ball_type = 3;
		}

		//for shooting projectiles
		if(k == SDL_SCANCODE_LEFT){
			xMov = -3;
			this->direction = 1;
		}if(k == SDL_SCANCODE_RIGHT){
			xMov = 3;
			this->direction = 2;
		}if(k == SDL_SCANCODE_UP){
			yMov = -3;
			this->direction = 3;
		}if(k == SDL_SCANCODE_DOWN){
			yMov = 3;
			this->direction = 4;
		}
	}
	if(xMov != 0 && yMov != 0){
		xMov = xMov/3;
		yMov = yMov/3;
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
		if((double)(((double)attackSpeed*(std::clock() - lastFired) / (double) (CLOCKS_PER_SEC)) > 1.0)){
			addProjectile(xMov,yMov,2000,1.0,1.0);
			lastFired = std::clock();
		}
	}
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
	renderXPBar(950, 20, 200, 25, percentOfXP(), colorSDL(3, 12, 80, 220), colorSDL(220, 230, 120, 220));
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
