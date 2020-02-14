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
	scene = new Scene();
	//character = new AnimatedSprite("girl","./resources/character/Idle_1.png");
	this->addChild(scene);
	scene->loadScene("test.json");

}

MyGame::~MyGame(){
	//scene.saveScene("test.json")
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
