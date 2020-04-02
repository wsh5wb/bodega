#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "Scene.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "MyGame.h"
#include "Player.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000){
	character = new AnimatedSprite("ENEMY_GIRL","./resources/character/floryan_head.png");
	character->showHitbox = true;
	coin = new AnimatedSprite("ENEMY_COIN","./resources/miscellaneous/Dogecoin_Logo.png");
	coin->moveTo(200,200);
	coin->showHitbox = true;
	me = new Player();
	me->showHitbox = true;


	double boundLow = 0.15;
	double boundHigh = 1 - boundLow;

	SDL_Point charHit[4];
	charHit[0] = {character->w*boundLow,character->h*boundLow};
	charHit[1] = {character->w*boundHigh,character->h*boundLow};
	charHit[3] = {character->w*boundLow,character->h*boundHigh};
	charHit[2] = {character->w*boundHigh,character->h*boundHigh};

	character->setHitbox(charHit);

	charHit[0] = {coin->w*boundLow,coin->h*boundLow};
	charHit[1] = {coin->w*boundHigh,coin->h*boundLow};
	charHit[3] = {coin->w*boundLow,coin->h*boundHigh};
	charHit[2] = {coin->w*boundHigh,coin->h*boundHigh};

	coin->setHitbox(charHit);
	//character->addAnimation("./resources/character/Dead","Dead",30,60,true);
	//cout << "play";
	//character->addAnimation("./resources/character/spritesheet.png","./resources/character/deadSheet.xml","Dead",1,60,true);
	//character->addAnimation("./resources/character/jumpsprites.png","./resources/character/jumpSheet.xml","Jump",1,60,false);
	//character->addAnimation("./resources/character/runSprite.png","./resources/character/runSheet.xml","Run",1,60,true);
	//character->addAnimation("./resources/character/idleSprite.png","./resources/character/idleSheet.xml","Idle",1,75,true);
	//character->play("Idle");
	// character->play("Dead");
	// character = new Scene();
	//bg = new Scene();
	//bg->loadScene("./resources/scenes/test3.txt");
	// character->loadScene("./resources/scenes/test.txt");

	charHit[0] = {me->w*boundLow, me->h*boundLow};
	charHit[1] = {me->w*boundHigh, me->h*boundLow};
	charHit[3] = {me->w*boundLow,me->h*boundHigh};
	charHit[2] = {me->w*boundHigh,me->h*boundHigh};

	me->setHitbox(charHit);

	this->addChild(character);
	this->addChild(coin);
	//cout << "Getting here." << endl;
	this->addChild(me);
	//this->addChild(bg);

	Game::cs.watchForCollisions("ENEMY", "PLAYER");
	//cout << me->type << endl;
	//cout << character->type << endl;
	//cout << coin->type << endl;
}

MyGame::~MyGame(){
//	std::ofstream o("./resources/scenes/test.txt");
//	o << "2 1" << std::endl;
//	o << "0 " << "Scene" << " "<< "0" << " " << "0" << " "<< "0" << " "<< "0" << " "<< "true" << " "<< "false"  << " "<< "0" << " "<< "0" << std::endl;
//	o << "3 " << character->id << " "<< character->imgPath << " " << character->red << " "<< character->green << " "<< character->blue << " "<< std::boolalpha << character->vis << " "<< std::boolalpha << character->isRGB << " "<< character->w << " "<< character->h << std::endl;
//	o << "Scene" << " " << character->id << std::endl;
	//cerr << character->numChildren();
}


void MyGame::update(set<SDL_Scancode> pressedKeys){

	Game::update(pressedKeys);
	DisplayObjectContainer::update(pressedKeys);
	for(SDL_Scancode code : pressedKeys){
		switch(code){

			case SDL_SCANCODE_W:
			{
				this->translateUp();
				//character->translateDown();
				break;
			}case SDL_SCANCODE_S:
			{
				this->translateDown();
				break;
			}case SDL_SCANCODE_A:
			{
				this->translateLeft();
				break;
			}case SDL_SCANCODE_D:
			{
				this->translateRight();
				break;
			}case SDL_SCANCODE_E:
			{
				this->rotateCW();
				break;
			}case SDL_SCANCODE_R:
			{
				this->rotateCCW();
				break;
			}case SDL_SCANCODE_F:
			{
				this->scaleIn();
				break;
			}case SDL_SCANCODE_G:
			{
				this->scaleOut();
				break;
			}

			//character
			case SDL_SCANCODE_I:
			{
				character->translateUp();
				break;
			}case SDL_SCANCODE_K:
			{
				character->translateDown();
				break;
			}case SDL_SCANCODE_J:
			{
				character->translateLeft();
				break;
			}case SDL_SCANCODE_L:
			{
				character->translateRight();
				break;
			}case SDL_SCANCODE_O:
			{
				character->rotateCW();
				break;
			}case SDL_SCANCODE_P:
			{
				character->rotateCCW();
				break;
			}case SDL_SCANCODE_N:
			{
				character->scaleIn();
				break;
			}case SDL_SCANCODE_M:
			{
				character->scaleOut();
				break;
			}

			//coin
			case SDL_SCANCODE_UP:
			{
				coin->translateUp();
				break;
			}case SDL_SCANCODE_DOWN:
			{
				coin->translateDown();
				break;
			}case SDL_SCANCODE_LEFT:
			{
				coin->translateLeft();
				break;
			}case SDL_SCANCODE_RIGHT:
			{
				coin->translateRight();
				break;
			}case SDL_SCANCODE_X:
			{
				coin->rotateCW();
				break;
			}case SDL_SCANCODE_C:
			{
				coin->rotateCCW();
				break;
			}case SDL_SCANCODE_V:
			{
				coin->scaleIn();
				break;
			}case SDL_SCANCODE_B:
			{
				coin->scaleOut();
				break;
			}
		}

	}
	// I think the cs update should be here to keep from rendering frames
	// where objects are overlapping one another.
	Game::cs.update();
	/*if(pressedKeys.count(SDL_SCANCODE_A) == 0 && pressedKeys.count(SDL_SCANCODE_D) == 0){
		if (character->playing && character->currAnimation == "Run"){
			character->stop();
			character->play("Idle");
		}
	}
	if(!character->playing && character->currAnimation == "Jump"){
		character->stop();
		character->play("Idle");
	}*/

}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
	DisplayObjectContainer::draw(at);
	// Game::cs.collidesWith(character,coin);
	SDL_RenderPresent(Game::renderer);
}
