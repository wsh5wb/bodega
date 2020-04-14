#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include "AnimatedSprite.h"
#include <vector>
#include <string>
#include <fstream>
#include "Sprite.h"
#include "Player.h"

using namespace std;

class Enemy : public Sprite{

public:
	Enemy(Player* player);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	//void onEnemyCollision(Enemy* enemy);
	void onMeleeStrike();
	void onEssenceStrike();
	void onCollision(DisplayObject* other);
	//virtual void draw(AffineTransform &at);
	void save(ofstream &out);
	void charge();
	void prepareCharge();
	void setPatrolRange();
	void patrol();
	void moveToTarget();
	bool isTargetReached();


	/* Health and such */
	int health = 100;
	int shield = 100;
	int maxHealth = 100;
	int maxShield = 100;

	//iFrames
	bool iFrames = false;
	int iFrameCount = 0;
	int numIFrames = 0;

	//variables
	int targX, targY;
	//int pivotX, pivotY;
	bool clean;
	int state;
	double vel;
	double maxVel, rotVel, maxRotVel;
	int minPatX, minPatY, maxPatX, maxPatY;
	int pauseCount;
	double acc, rotAcc;
	Player* player;

	/* Current Enemy player is engaging with*/
	//Enemy* curEnemy = NULL;

private:

	int oldX=0, oldY=0;

	int _jumpVel = -15;

	/* Falling variables */
	bool _standing = false;
	int _maxFall = 9;
	int _yAcc = 2; //one pixel every two frames
	int _yAccCount = 0;
	int _yVel = 0;

	void initIFrames(int numFrames);

};

#endif
