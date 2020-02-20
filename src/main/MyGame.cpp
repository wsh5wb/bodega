#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "Scene.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000){
	//game = new DisplayObjectContainer();
	character = new Scene();
	//character = new AnimatedSprite("girl","./resources/character/Idle_1.png");
	//character = new Sprite("character", "./resources/character/Idle_1.png");
	this->addChild(character);
	this->scene = "./resources/scenes/test.txt";
	character->loadScene(scene);
	effect.loadMusic("./resources/sounds/clock_ticking.wav");
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

			case SDL_SCANCODE_DOWN:
			{
				character->translateUp();
				break;
			}case SDL_SCANCODE_UP:
			{
				character->translateDown();
				break;
			}case SDL_SCANCODE_LEFT:
			{
				character->translateRight();
				break;
			}case SDL_SCANCODE_RIGHT:
			{
				character->translateLeft();
				break;
			}case SDL_SCANCODE_Q:
			{
				character->scaleOut();
				break;
			}case SDL_SCANCODE_W:
			{
				character->scaleIn();
				break;
			}case SDL_SCANCODE_A:
			{
				character->rotateCW();
				break;
			}case SDL_SCANCODE_S:
			{
				character->rotateCCW();
				break;
			}
			case SDL_SCANCODE_I: 
			{
				character->movePivotUp();
				break;
			}case SDL_SCANCODE_J:
			{
				character->movePivotLeft();
				break;
			}case SDL_SCANCODE_K:
			{
				character->movePivotDown();
				break;
			}case SDL_SCANCODE_L:
			{
				character->movePivotRight();
				break;

			}case SDL_SCANCODE_Z:
			{
				character->increaseAlpha();
				break;
			}case SDL_SCANCODE_X:
			{
				character->decreaseAlpha();
				break;
			}

			case SDL_SCANCODE_P:
			{
				effect.playMusic();
				break;
			}
		}
	}

}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
	DisplayObjectContainer::draw(at);
	SDL_RenderPresent(Game::renderer);
}
