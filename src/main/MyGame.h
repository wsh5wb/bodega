#ifndef MYGAME_H
#define MYGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include "Scene.h"
#include "Sound.h"
#include "Camera.h"
#include "myCoin.h"
#include "QuestManager.h"
#include "TweenJuggler.h"
#include "DemoDungeon.h"
#include "HadesDungeon.h"
#include "CollisionSystem.h"
#include "Enemy.h"

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

private:
	Camera* myCamera;
	Scene *character;
	Enemy *enemy;
	CollisionSystem cs;
	//Scene* character;

	string scene;
	Sound effect;
	HadesDungeon* dungeon;
	TweenJuggler * animationJuggler;
};

#endif
