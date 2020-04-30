#ifndef SPIRIT_H
#define SPIRIT_H

#include "Enemy.h"

using namespace std;

class Spirit : public Enemy{

public:
  Spirit(Player* player);
  Spirit(Player* player, int d);

  virtual void update(set<SDL_Scancode> pressedKeys);
  virtual void draw(AffineTransform &at);

  int timer;
  int xSpe, ySpe;
  int xBound, yBound;
  SDL_Point globalPos;
};

#endif
