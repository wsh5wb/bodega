#ifndef JELLY_H
#define JELLY_H

#include "Enemy.h"

using namespace std;

class Jelly : public Enemy{

public:
  Jelly(Player* player);
  Jelly(Player* player, int d);

  virtual void update(set<SDL_Scancode> pressedKeys);
  virtual void draw(AffineTransform &at);

  int timer;
  string path;
  int xBound, yBound;
  int projectileDamage = 5;
  int projectileSpeed = 0;
  int maxCoolDown = 200;
  int nextShot = 0;
  int type; 

};

#endif
