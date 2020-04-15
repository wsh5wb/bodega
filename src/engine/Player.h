#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "AnimatedSprite.h"
#include <vector>
#include <string>
#include <fstream>
#include "Game.h"
#include "Sprite.h"
#include "TweenJuggler.h"

using namespace std;

class Player : public AnimatedSprite{

public:
	Player();

	static Player* getPlayer();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	//void onEnemyCollision(Enemy* enemy);
	virtual void onCollision(DisplayObject* other);
	virtual void saveSelf(vector<string> &objects, vector<string> &dependencies);
	virtual void renderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
	virtual float percentOfHealthLost();
	/* Health and such */

	//iFrames
	bool iFrames = false;
	int iFrameCount = 0;
	int numIFrames = 0;



	/* Current Enemy player is engaging with*/
	//Enemy* curEnemy = NULL;

private:

	int health = 114;
	int maxHealth = 320;

	int oldX=0, oldY=0;

	int _jumpVel = -15;

	/* Falling variables */
	bool _standing = false;
	int _maxFall = 9;
	int _yAcc = 2; //one pixel every two frames
	int _yAccCount = 0;
	int _yVel = 0;

	static Player* player;
	void initIFrames(int numFrames);

};

#endif
