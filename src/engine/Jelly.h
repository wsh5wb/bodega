#ifndef JELLY_H
#define JELLY_H

#include "Enemy.h"

using namespace std;

class Jelly : public Enemy{

public:
  Jelly(Player* player);

  virtual void update(set<SDL_Scancode> pressedKeys);
  virtual void draw(AffineTransform &at);

  int timer;
  int xSpe, ySpe;
  int xBound, yBound;
};

#endif
