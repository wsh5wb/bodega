#include "Urchin.h"
#include "DisplayObjectContainer.h"
#include <cstdlib>

using namespace std;

Urchin::Urchin(Player *player) :
		Enemy(player) {
	this->loadTexture("resources/enemies/gordo_one.png");
	this->id = "ENEMY_Urchin";
	this->scaleX *= 0.5;
	this->scaleY *= 0.5;
	//this->pivot.x = w * scaleX / 2;
	//this->pivot.y = h * scaleY / 2;
	xSpe = 0;
	ySpe = 0;
	state = 0;
}

void Urchin::update(set<SDL_Scancode> pressedKeys) {
	Sprite::update(pressedKeys);
	if (state == 0) {
		timer++;
		if (timer <= 360) {
			if (timer % 30 == 0)
				this->increaseAlpha();
		}
		if (timer > 360) {
			timer = 0;
			this->scaleX = .8;
			this->scaleY = .8;
			//this->setHitbox(-.5, 1.5);
			std::cout << "state2 urchin" << '\n';
			state++;
		}

	} else if (state == 1) {
		state++;
	} else if (state == 2) {
		timer++;
		if (timer <= 360) {

		}
		if (timer > 360) {
			this->scaleX = .5;
			this->scaleY = .5;
			//this->setHitbox(0, 1);
			this->setAlpha(100);
			timer = 0;
			state = 0;
		}
	}else{
		state = 0;
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

void Urchin::draw(AffineTransform &at) {
	Enemy::draw(at);
}
