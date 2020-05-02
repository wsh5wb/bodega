#ifndef SKEL_H
#define SKEL_H

#include <iostream>
#include "AnimatedSprite.h"
#include "Player.h"
#include "Enemy.h"

using namespace std;

class Skel : public Enemy{
public:
  Skel(Player * player);

  virtual void update(set<SDL_Scancode> pressedKeys);
  virtual void draw(AffineTransform &at);

  void hide();
  void axeAttack();

  int idleTime = 0;
  int chaseTime = 0;
  int attackTime = 0;
};

#endif
