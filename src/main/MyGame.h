#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "AnimatedSprite.h"
#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include "Scene.h"
#include "myCoin.h"
#include "QuestManager.h"
#include "CollisionSystem.h"

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

private:
	AnimatedSprite *character;
	AnimatedSprite *coin;
	CollisionSystem cs;
	//Scene* character;
	string scene;
	bool changed;
	Coin* myCoin;
	bool isQuestDone;

};

#endif
