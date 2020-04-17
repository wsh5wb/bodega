#include "Urchin.h"
#include "DisplayObjectContainer.h"
#include <cstdlib>

using namespace std;

Urchin::Urchin(Player* player) : Enemy(player){
  this->loadTexture("resources/enemies/gordo_one.png");
  this->id = "ENEMY_Urchin";
  this->scaleX *= 0.5;
  this->scaleY *= 0.5;
  xSpe = 0;
  ySpe = 0;
  state = 0;
}

void Urchin::update(set<SDL_Scancode> pressedKeys){
  Sprite::update(pressedKeys);
  if (state == 0){
    timer++;
    if (timer <= 360){
      this->decreaseAlpha();
    }
    if (timer > 360){
      state++;
    }

  }
  else if (state == 1){
    //timer++;
    //if (timer >= 360){
      timer = 0;
      std::cout << "state2 urchin" << '\n';
      state--;
    //}
  }
//   cout << position.x << ", " << position.y << endl;
//   position.x += xSpe;
//   position.y += ySpe;
//   if (position.x == 0 || position.x == xBound){
//     xSpe *= -1;
//   }
//   if (position.y == 0 || position.y == yBound){
//     ySpe *= -1;
//   }
}

void Urchin::draw(AffineTransform &at){
  Enemy::draw(at);
}
