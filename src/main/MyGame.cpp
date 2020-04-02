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
}

MyGame::~MyGame(){}

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
//	myCamera->draw(at);
	SDL_RenderClear(Game::renderer);
	DisplayObjectContainer::draw(at);	
	// Game::cs.collidesWith(character,coin);

	SDL_RenderPresent(Game::renderer);
}
