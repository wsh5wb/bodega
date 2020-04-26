#include "Urchin.h"
#include "DisplayObjectContainer.h"
#include <cstdlib>
#include "Projectile.h"
#include "DTEvent.h"

using namespace std;

Urchin::Urchin(Player *player) :
		Enemy(player) {
	this->loadTexture("resources/enemies/gordo_one.png");
	this->id = "ENEMY_Urchin";
	this->scaleX *= 0.5;
	this->scaleY *= 0.5;
	//this->pivot.x = w * scaleX / 2;
	//this->pivot.y = h * scaleY / 2;
	xSpe = 2;
	ySpe = 2;
	state = 0;
	this->xBound = 512 - (w * scaleX);
	this->yBound = 384 - (h * scaleY);
	this->xp = 10;
}

Urchin::Urchin(Player *player, int d) :
		Enemy(player) {
	this->type = d;
	switch (d) {
		case 0: {
			this->loadTexture("resources/enemies/gordo_one.png");
			this->id = "ENEMY_Urchin";
			this->scaleX *= 0.5;
			this->scaleY *= 0.5;
			//this->pivot.x = w * scaleX / 2;
			//this->pivot.y = h * scaleY / 2;
			xSpe = 2;
			ySpe = 2;
			state = 0;
			this->xBound = 512 - (w * scaleX);
			this->yBound = 384 - (h * scaleY);
			this->xp = 10;
			break;
		}case 2: {
			this->loadTexture("resources/enemies/gordo_one.png");
			this->id = "ENEMY_Urchin";
			this->scaleX *= 0.5;
			this->scaleY *= 0.5;
			//this->pivot.x = w * scaleX / 2;
			//this->pivot.y = h * scaleY / 2;
			xSpe = 2;
			ySpe = 2;
			state = 0;
			this->xBound = 512 - (w * scaleX);
			this->yBound = 384 - (h * scaleY);
			projectileDamage = 10;
			this->xp = 20;
			break;
		}
		default: {
			this->loadTexture("resources/enemies/gordo_one.png");
			this->id = "ENEMY_Urchin";
			this->scaleX *= 0.5;
			this->scaleY *= 0.5;
			//this->pivot.x = w * scaleX / 2;
			//this->pivot.y = h * scaleY / 2;
			xSpe = 2;
			ySpe = 2;
			state = 0;
			this->xBound = 512 - (w * scaleX);
			this->yBound = 384 - (h * scaleY);
			this->xp = 10;
			break;
		}
	}

}

void Urchin::update(set<SDL_Scancode> pressedKeys) {
	Sprite::update(pressedKeys);
	if (state == 0) {
		timer++;
		if (timer <= 180) {
			if (timer % 15 == 0)
				this->increaseAlpha();
		}
		if (timer > 180) {
			timer = 0;
			this->scaleX = .8;
			this->scaleY = .8;
			this->translate(-w * scaleX * .625 / 4, h * -scaleY * .625 / 4);
			//this->setHitbox(-.5, 1.5);
			std::cout << "state2 urchin" << '\n';
			state++;
		}

	} else if (state == 1) {
		if(type < 2){
			state++;
			return;
		}
		timer++;
		if (timer % 50 == 0) {
			cout << "FIRED" << endl;
			//Generate projectiles 
			string path = "resources/Projectiles/spikedball.png";
			int midX = this->position.x + (dstrect.w)/3;
		    int midY = this->position.y + (dstrect.h)/3;
		    cout << ((DisplayObjectContainer*)this->parent)->numChildren() << endl;
			Projectile * p = new Projectile(path, midX, midY,0,3,500,0.25,0.25,projectileDamage);
			cout << ((DisplayObjectContainer*)this->parent)->numChildren() << endl;
			((DisplayObjectContainer*)this->parent)->addChild(p);
			DTEvent e("OBJ_ADD", &Game::eventHandler, p);
			Game::eventHandler.dispatchEvent(&e);
		}
		if (timer > 200) {
			timer = 0;
			state++;
		}
		//state++;
	} else if (state == 2) {
		timer++;
		if (timer <= 360) {

		}
		if (timer > 180) {
			this->translate(w * scaleX * .625 / 4, h * scaleY * .625 / 4);
			this->scaleX = .5;
			this->scaleY = .5;
			//this->setHitbox(0, 1);
			this->setAlpha(100);
			timer = 0;
			state++;
		}
	} else if (state == 3) {
		timer++;
		if (timer <= 360) {
			position.x += xSpe;
			position.y += ySpe;
			if (position.x <= 0 || position.x >= xBound) {
				xSpe *= -1;
			}
			if (position.y <= 0 || position.y >= yBound) {
				ySpe *= -1;
			}
		}
		if (timer > 360) {
			timer = 0;
			state = 0;
		}

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
