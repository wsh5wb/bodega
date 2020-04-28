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

  int health = 500;
  int maxHealth = 500;
  int prowlTime = 0;
  int lungeTime = 0;
  int restCount = 0;
  vector<Projectile*> projectiles;
};

#endif
