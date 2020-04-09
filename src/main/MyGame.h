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
<<<<<<< HEAD
#include "DemoDungeon.h"
=======
#include "CollisionSystem.h"
#include "Enemy.h"
>>>>>>> 291dbf5ee98878889e449e43b809b041231399cc

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
	DemoDungeon* dungeon;
};

#endif
