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
#include "Projectile.h"
#include "TextBox.h"
#include "StatMenu.h"

#define LEVELS 					255
#define PROJECTILE_SWAP_FRAMES 	30
#define IFRAME_COUNT			180
#define PROJ_SPEED				6

using namespace std;

class Player : public AnimatedSprite{

public:
	Player();
	virtual ~Player();

	static Player* getPlayer();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	//void onEnemyCollision(Enemy* enemy);
	virtual void onCollision(DisplayObject* other);
	virtual void saveSelf(vector<string> &objects, vector<string> &dependencies);
	virtual void renderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
	virtual void renderXPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
	virtual float percentOfHealthLost();
	virtual float percentOfXP();
	int getHealth();
	int getMaxHealth();
	double getSpeed();
	double getDamage();
	double getAttackSpeed();
	int getLevel();
	bool changeHealth(int value);
	void changeMaxHealth(int value);
	void changeDamage(int value);
	void changeAttackSpeed(double value);
	void toggleHealthDisplay();
	bool checkLevelUp();
	void levelUp();
	void changeXP(int value);
	void modifySpeed(int value);
	void addProjectile(int speedX, int speedY, int timeout, double scaleX, double scaleY);
	/* Health and such */
	int damage = 100;
	int slow = 1;
	int lifesteal = 20;

	double attackSpeed = 1;

	//iFrames
	bool iFrames = false;
	int iFrameCount = 0;
	int numIFrames = 0;


	vector<Projectile*> projectiles;
	/* Current Enemy player is engaging with*/
	//Enemy* curEnemy = NULL;

private:
	unsigned int xp = 0;
	unsigned int level = 1, maxLevel = LEVELS;
	//unsigned int xpChart[LEVELS-1] = {10,25,50,100};
	double xpScale = 1.5;
	unsigned int xpNeeded = 10;
	int health = 8;
	int maxHealth = 8;
	bool displayHealth = true;
	int runSpeed = 4;
	int current_ball_type = 1;
	int direction = 1;

	int oldX=0, oldY=0;

	int _jumpVel = -15;

	/* Falling variables */
	bool _standing = false;
	int _maxFall = 9;
	int _yAcc = 2; //one pixel every two frames
	int _yAccCount = 0;
	int _yVel = 0;
	TextBox * chat_box;
	StatMenu * my_stats;
	std::clock_t lastFired = 0;

	static Player* player;
	uint projSwapDelay = 0;
	void initIFrames(int numFrames);

};

#endif
