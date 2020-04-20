#include "Jelly.h"
#include "DisplayObjectContainer.h"
#include <cstdlib>

using namespace std;

Jelly::Jelly(Player* player) : Enemy(player){
  this->loadTexture("resources/enemies/jelly.png");
  this->id = "ENEMY_Jellyfish";
  this->scaleX *= 0.1;
  this->scaleY *= 0.1;
  this->xBound=512-(w*scaleX);
  this->yBound=384-(h*scaleY);
  xSpe = 1;
  ySpe = 1;
  state = 0;
}

void Jelly::update(set<SDL_Scancode> pressedKeys){
  Sprite::update(pressedKeys);
  if (state == 0){
    timer++;
    if (timer >= 180){
      state++;
    }
  }
  else if (state == 1){
    timer++;
    if (timer >= 360){
      timer = 0;
    }
  }
  cout << position.x << ", " << position.y << endl;
  position.x += xSpe;
  position.y += ySpe;
  if (position.x <= 0 || position.x >= xBound){
    xSpe *= -1;
  }
  if (position.y <= 0 || position.y >= yBound){
    ySpe *= -1;
  }
}

void Jelly::draw(AffineTransform &at){
  Enemy::draw(at);
}
