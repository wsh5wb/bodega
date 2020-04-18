#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "Scene.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "MyGame.h"
#include "TweenJuggler.h"

using namespace std;
/*	this->alpha = 0;
 printf("1");
 TweenJuggler * juggle = TweenJuggler::getInstance();
 printf("1");
 Tween * alpha_tween = new Tween(this);
 printf("1");
 alpha_tween->animate(TWEEN_ALPHA, this->alpha, 255, 100, TWEEN_LINEAR, EASE_IN);
 printf("1");
 juggle->add(alpha_tween);*/

MyGame::MyGame() :
		Game(1200, 900) {
	Game::eventHandler.addEventListener((EventListener*) Game::cs, "OBJ_ADD");
	Game::eventHandler.addEventListener((EventListener*) Game::cs, "OBJ_RM");

	myCamera = Camera::getCamera();
	// dungeon = new OceanDungeon();
	dungeon = new HadesDungeon();
	dungeon->generate();
	myCamera->addScene(dungeon);
	hades_theme.loadMusic("./resources/sounds/lullaby.wav");
	effect.loadMusic("./resources/sounds/clock_ticking.wav");
	hades_theme.playMusic();
	animationJuggler = TweenJuggler::getInstance();
	addChild(myCamera->container);

//	enemy = new Enemy((Player*) character->getChild("PLAYER_YOU"));
//
//	this->addChild(character);
//	this->addChild(enemy);
//
//	Game::cs.watchForCollisions("ENEMY", "PLAYER");
	Game::cs->watchForCollisions("PLAYER", "DOOR");
	Game::cs->watchForCollisions("PLAYER", "OBSTACLE");
	Game::cs->watchForCollisions("PROJECTILE","OBSTACLE");

	// Come up with more elegant solution to determining which dir to go.
	Game::eventHandler.addEventListener((EventListener*) dungeon,
			"DUNG_TRANS_U");
	Game::eventHandler.addEventListener((EventListener*) dungeon,
			"DUNG_TRANS_D");
	Game::eventHandler.addEventListener((EventListener*) dungeon,
			"DUNG_TRANS_R");
	Game::eventHandler.addEventListener((EventListener*) dungeon,
			"DUNG_TRANS_L");
}

MyGame::~MyGame() {

	Scene *character = new Scene();
	character->addChild(myCamera->container);
	//character->saveScene("./resources/scenes/testSave3.txt");
//	std::ofstream o("./resources/scenes/test.txt");
//	o << "2 1" << std::endl;
//	o << "0 " << "Scene" << " "<< "0" << " " << "0" << " "<< "0" << " "<< "0" << " "<< "true" << " "<< "false"  << " "<< "0" << " "<< "0" << std::endl;
//	o << "3 " << character->id << " "<< character->imgPath << " " << character->red << " "<< character->green << " "<< character->blue << " "<< std::boolalpha << character->vis << " "<< std::boolalpha << character->isRGB << " "<< character->w << " "<< character->h << std::endl;
//	o << "Scene" << " " << character->id << std::endl;
	//cerr << character->numChildren();
}

void MyGame::update(set<SDL_Scancode> pressedKeys) {

	Game::update(pressedKeys);
	DisplayObjectContainer::update(pressedKeys);
	myCamera->update(pressedKeys);

	for (SDL_Scancode code : pressedKeys) {
		switch (code) {

		case SDL_SCANCODE_P: {
			hades_theme.playMusic();
			break;
		}
		}
	}

	Game::cs->update();
	this->resetDelta();
}

void MyGame::draw(AffineTransform &at) {
	Game::draw(at);
//	myCamera->draw(at);
	SDL_RenderClear(Game::renderer);
	myCamera->draw(at);
	DisplayObjectContainer::draw(at);
	animationJuggler->nextFrame();
	SDL_RenderPresent(Game::renderer);
}
