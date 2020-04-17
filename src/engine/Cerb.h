#ifndef CERB_H
#define CERB_H

#include <iostream>
#include "AnimatedSprite.h"
#include "Player.h"
#include "Enemy.h"

using namespace std;

class Cerb : public Enemy{
public:
  Cerb(Player* player);

  virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

  void onHit();
  void patrol();
  void rush();
  void lunge();
  void shoot();
  void moveToTarget();
  bool isTargetReached();

  int health = 500;
  int maxHealth = 500;
  int prowlTime = 0;
};

#endif
