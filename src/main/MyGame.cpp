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

	itemSys = new ItemSystem();
	// Dungeon generation
	dunMan = new DungeonManager();

	printf("Generating Ocean\n");
	Dungeon *dungeon = new HadesDungeon();
	dungeon->generate();
	dunMan->activeDungeon = dungeon;
	myCamera->addScene(dunMan->activeDungeon);

	// Music and tweens
	hades_theme.loadMusic("./resources/sounds/lullaby.wav");
	effect.loadMusic("./resources/sounds/clock_ticking.wav");
	hades_theme.playMusic();
	animationJuggler = TweenJuggler::getInstance();
	addChild(myCamera->container);

	// Collision setup
	Game::cs->watchForCollisions("PLAYER", "OBSTACLE");
	Game::cs->watchForCollisions("PLAYER", "FLOOR");
	Game::cs->watchForCollisions("PLAYER", "ENEMY");
	Game::cs->watchForCollisions("PLAYER", "PORTAL");
	Game::cs->watchForCollisions("PLAYER", "chest");
	Game::cs->watchForCollisions("PROJECTILE", "OBSTACLE");
	Game::cs->watchForCollisions("PROJECTILE", "ENEMY");

	// Initial event watching
	Game::eventHandler.addEventListener((EventListener*) dunMan,
			"CHANGE_DUNGEON");
	Game::eventHandler.addEventListener((EventListener*) dunMan,
			"PLAYER_KILLED");
	Game::eventHandler.addEventListener((EventListener*) itemSys,
			"CHEST_OPENED");

	player_stats = new StatMenu();
	Game::eventHandler.addEventListener((EventListener*) player_stats,
			"STATS_CHANGED");
	Player::getPlayer()->addChild(player_stats);
}

MyGame::~MyGame() {

	//Scene *character = new Scene();
	//character->addChild(myCamera->container);

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
		case SDL_SCANCODE_O: {
			Event e("ENEMY_KILLED", &Game::eventHandler);
			Game::eventHandler.dispatchEvent(&e);
			SDL_Delay(50);
			break;
		}
		case SDL_SCANCODE_SPACE: {
			Event e("CHANGE_DUNGEON", &Game::eventHandler);
			Game::eventHandler.dispatchEvent(&e);
			SDL_Delay(100);
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
	// myCamera->draw(at);
	DisplayObjectContainer::draw(at);
	animationJuggler->nextFrame();
	SDL_RenderPresent(Game::renderer);
}
