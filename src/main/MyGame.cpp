#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "DisplayObject.h"
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000){
	//game = new DisplayObjectContainer();
	character = new AnimatedSprite("girl", "./resources/character/Idle_1.png");
	myCoin = new Coin("coin","./resources/miscellaneous/Dogecoin_Logo.png");
	QuestManager* CoinQuest = new QuestManager();
	myCoin->addEventListener(CoinQuest, "COIN_PICKED_UP");

	myCoin->movePivot(myCoin->w/2, myCoin->h/2);
	myCoin->scale(.25);
	myCoin->moveTo(600, 500);
	character->scale(.5);
	character->moveTo(character->w/2, 500);
	character->movePivot(character->w/2, character->h/2);
	this->addChild(myCoin);
	this->addChild(character);

	isQuestDone = false;

}

MyGame::~MyGame(){

}


void MyGame::update(set<SDL_Scancode> pressedKeys){

	Game::update(pressedKeys);
	DisplayObjectContainer::update(pressedKeys);

	for(SDL_Scancode code : pressedKeys){
		switch(code){

			case SDL_SCANCODE_DOWN:
			{
				character->translateDown();
				break;
			}case SDL_SCANCODE_UP:
			{
				character->translateUp();
				break;
			}case SDL_SCANCODE_LEFT:
			{
				character->translateLeft();
				break;
			}case SDL_SCANCODE_RIGHT:
			{
				character->translateRight();
				break;
			}
			//case SDL_SCANCODE_Q:
			// {
			// 	character->scaleOut();
			// 	break;
			// }case SDL_SCANCODE_W:
			// {
			// 	character->scaleIn();
			// 	break;
			// }case SDL_SCANCODE_A:
			// {
			// 	character->rotateCW();
			// 	break;
			// }case SDL_SCANCODE_S:
			// {
			// 	character->rotateCCW();
			// 	break;
			// }
			// case SDL_SCANCODE_I: 
			// {
			// 	character->movePivotUp();
			// 	break;
			// }case SDL_SCANCODE_J:
			// {
			// 	character->movePivotLeft();
			// 	break;
			// }case SDL_SCANCODE_K:
			// {
			// 	character->movePivotDown();
			// 	break;
			// }case SDL_SCANCODE_L:
			// {
			// 	character->movePivotRight();
			// 	break;

			// }case SDL_SCANCODE_Z:
			// {
			// 	character->increaseAlpha();
			// 	break;
			// }case SDL_SCANCODE_X:
			// {
			// 	character->decreaseAlpha();
			// 	break;
			// }

			// case SDL_SCANCODE_P:
			// {
			// 	break;
			// }
		}
	}
	SDL_Point char_piv = character->getPosition();
	SDL_Point coin_piv = myCoin->getPosition();
	double distance = character->dist(char_piv, coin_piv);

	if( distance < 50 && !isQuestDone ){
		isQuestDone = true;
		myCoin->makeInvisible();
		myCoin->dispatchEvent();
	}

}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);

	SDL_RenderClear(Game::renderer);
	DisplayObjectContainer::draw(at);
	SDL_RenderPresent(Game::renderer);
}