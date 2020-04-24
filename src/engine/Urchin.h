#ifndef URCHIN_H
#define URCHIN_H

#include "Enemy.h"

using namespace std;

class Urchin : public Enemy{

public:
  Urchin(Player* player);
  Urchin(Player* player, int d);

  virtual void update(set<SDL_Scancode> pressedKeys);
  virtual void draw(AffineTransform &at);

  int timer = 0;
  int xSpe, ySpe;
  int xBound, yBound;
};

#endif
