#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "DisplayObject.h"
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000){
	//game = new DisplayObjectContainer();
	character = new AnimatedSprite("girl","./resources/character/Idle_1.png");
	this->addChild(character);
	character->addAnimation("./resources/character/Idle","Idle",16,1,true);
	character->addAnimation("./resources/character/Dead","Dead",30,1,true);
	character->play("Idle");
	characterPlaying = true;
	//cout << game->numChildren();
	//character = new DisplayObjectContainer("sun","./resources/planets/planet/soleil.png");
	character->moveTo(600,400);
	character->scale(.3);
	character->movePivot(character->w/2,character->h/2);
	
	earth = new DisplayObjectContainer("earth","./resources/planets/planet/terre.png");
	
	DisplayObjectContainer* mercury = new DisplayObjectContainer("mercury","./resources/planets/planet/mercure.png");
	//mercury->moveTo(100,0);
	DisplayObjectContainer* venus = new DisplayObjectContainer("venus","./resources/planets/planet/venus.png");
	//venus->moveTo(60,0);
	DisplayObjectContainer* mars = new DisplayObjectContainer("mars","./resources/planets/planet/mars.png");
	//mars->moveTo(200,0);
	DisplayObjectContainer* planets = new DisplayObjectContainer();
	DisplayObjectContainer* earthCon = new DisplayObjectContainer();
	DisplayObjectContainer* earthMoons = new DisplayObjectContainer();
	DisplayObjectContainer* mercuryCon = new DisplayObjectContainer();
	DisplayObjectContainer* venusCon = new DisplayObjectContainer();
	DisplayObjectContainer* marsCon = new DisplayObjectContainer();

	DisplayObjectContainer* earthMoon = new DisplayObjectContainer("earthMoon","./resources/planets/planet/mercure.png");
	earth->movePivot(earth->w/2,earth->h/2);
	earthMoon->moveTo(65,0);
	earthMoons->addChild(earthMoon);

	earthMoons->scale(0.5);
	earthCon->addChild(earth);
	earthCon->scale(1/.3);
	marsCon->scale(1/.3);
	mercuryCon->scale(1/.3);
	venusCon->scale(1/.3);
	earth->addChild(earthMoons);
	mercuryCon->addChild(mercury);
	venusCon->addChild(venus);
	marsCon->addChild(mars);

	character->addChild(earthCon);
	character->addChild(mercuryCon);
	character->addChild(venusCon);	
	character->addChild(marsCon);


	//planets->addChild(mercury);
	//planets->addChild(venus);
	//planets->addChild(mars);
	//character->addChild(planets);
	//game->addChild(character);
	mercury->moveTo(120,0);
	venus->moveTo(-160,0);
	earth->moveTo(220,0);
	//earth->moveTo(character->w/2,character->h/2);
	//earth->movePivot(0,0);
	mars->moveTo(-280,0);
	//planets->movePivot(-10,-10);
	mercuryCon->setRotation(5);
	earthCon->setRotation(5.5);
	venusCon->setRotation(6);
	marsCon->setRotation(6.5);
	//earth->moveTo(600,0);
	//planets->movePivot(-600,-400);
	//cout << "Earth " << earth->getRotation() << endl;
	//cout << "Mercury " << mercury->getRotation() << endl;
	//cout << character->dist(SDL_Point(0,1),SDL_Point(1,0)) << endl;
	//this->addChild(character);

}

MyGame::~MyGame(){
	//delete character;
}


void MyGame::update(set<SDL_Scancode> pressedKeys){

	Game::update(pressedKeys);
	DisplayObjectContainer::update(pressedKeys);
	//game->update(pressedKeys);
	for(DisplayObject *child : character->children){
		child->rotateCW();
	}
	earth->getChild(0)->rotateCW();


	//character->getChild(0)->rotateCW();
	//character->getChild(1)->rotateCW();
	//AffineTransform at = AffineTransform();
	bool pUsed = false;
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
				pUsed = true;
				//character->toggleVisibility();
				if(!characterPlaying2){
					character->play("Dead");
					characterPlaying = false;
					characterPlaying2 = true;
				}break;
			}
		}
	}

	if(!pUsed && !characterPlaying){
		character->play("Idle");
		characterPlaying = true;
		characterPlaying2 = false;
	}


	//draw(at);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);

	SDL_RenderClear(Game::renderer);
	DisplayObjectContainer::draw(at);
	SDL_RenderPresent(Game::renderer);
}