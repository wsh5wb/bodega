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
	character = new AnimatedSprite("girl","./resources/character/Dead_1.png");
	//character->addAnimation("./resources/character/Dead","Dead",30,60,true);
	//cout << "play";
	character->addAnimation("./resources/character/spritesheet.png","./resources/character/deadSheet.xml","Dead",1,60,true);
	character->addAnimation("./resources/character/jumpsprites.png","./resources/character/jumpSheet.xml","Jump",1,60,false);
	character->addAnimation("./resources/character/runSprite.png","./resources/character/runSheet.xml","Run",1,60,true);
	character->addAnimation("./resources/character/idleSprite.png","./resources/character/idleSheet.xml","Idle",1,75,true);
	character->play("Idle");
	// character->play("Dead");
	// character = new Scene();
	// character->loadScene("./resources/scenes/test.txt");
	this->addChild(character);
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

			case SDL_SCANCODE_S:
			{
				character->translateDown();
				break;
			}case SDL_SCANCODE_SPACE:
			{
				if(character->currAnimation != "Jump")
					character->play("Jump");
				character->translateUp();
				break;
			}case SDL_SCANCODE_A:
			{
				if(character->currAnimation != "Run")
					character->play("Run");
				character->translateLeft();
				break;
			}case SDL_SCANCODE_D:
			{
				if(character->currAnimation != "Run")
					character->play("Run");
				character->translateRight();
				break;
			}
		}
			
	}
	if(pressedKeys.count(SDL_SCANCODE_A) == 0 && pressedKeys.count(SDL_SCANCODE_D) == 0){
		if (character->playing && character->currAnimation == "Run"){
			character->stop();
			character->play("Idle");
		}
	}
	if(!character->playing && character->currAnimation == "Jump"){
		character->stop();
		character->play("Idle");
	}

}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
	DisplayObjectContainer::draw(at);
	SDL_RenderPresent(Game::renderer);
}
