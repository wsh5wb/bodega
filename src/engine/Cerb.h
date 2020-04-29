#ifndef CERB_H
#define CERB_H

#include <iostream>
#include "AnimatedSprite.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include <vector>

using namespace std;

class Cerb : public Enemy{
public:
  Cerb(Player* player);

  virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

  void shoot();
  bool wasHit();
  bool atWall();
  void addProjectile(int speedX, int speedY, int timeout, double scaleX, double scaleY);

  int health = 5000;
  int maxHealth = 5000;
  int prowlTime = 0;
  int lungeTime = 0;
  int restCount = 0;
  int maxDist = 0;
  int originX;
  int originY;
  vector<Projectile*> projectiles;
};

#endif
