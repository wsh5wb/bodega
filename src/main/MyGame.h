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
#include "OceanDungeon.h"
#include "CollisionSystem.h"
#include "DungeonManager.h"
#include "Enemy.h"
#include "Jelly.h"
#include "Cerb.h"
#include "Urchin.h"
#include "ItemSystem.h"
#include "Player.h"

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

	DungeonManager* dunMan;
	ItemSystem* itemSys;
	string scene;
	bool changed;
	bool isQuestDone;
	TweenJuggler * animationJuggler;
	StatMenu * player_stats;
	bool DEBUG_CHANGE_STUFF=false;
};

#endif
