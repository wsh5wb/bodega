#ifndef CHARYBDIS_H
#define CHARYBDIS_H

#include <iostream>
#include "AnimatedSprite.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "DTEvent.h"
#include <vector>

using namespace std;

class charybdis : public Enemy{
public:
  charybdis(Player* player);
  charybdis(Player* player, int d);
  virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

    // void shoot(SDL_Point charLoc, SDL_Point globalPos);
    // bool wasHit();
    // bool atWall();
    // void addProjectile(int speedX, int speedY, int timeout, double scaleX, double scaleY);

  int health = 5000;
  int maxHealth = 5000;
  int prowlTime = 0;
  int lungeTime = 0;
  int restCount = 0;
  int maxDist = 0;
  int projectileSpeed = 3;
  int projectileDamage = 10;
  int originX;
  int originY;

  //vector<Projectile*> projectiles;
};

#endif
