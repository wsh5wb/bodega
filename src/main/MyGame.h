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
=======
#include "CollisionSystem.h"
#include "Player.h"
#include "Enemy.h"
>>>>>>> enemyDemo

using namespace std;

class MyGame : public Game{

public:
	MyGame();
	virtual ~MyGame();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

private:
<<<<<<< HEAD
	Camera* myCamera;
	Scene* character;
=======
	AnimatedSprite *character;
	AnimatedSprite *coin;
	Player *me;
	Scene *bg;
	Enemy *en;
	CollisionSystem cs;
	//Scene* character;
>>>>>>> enemyDemo
	string scene;
	Sound effect;
};

#endif
