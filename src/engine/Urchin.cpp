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
	xSpe = 1;
	ySpe = 1;
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
		health = 35;
		this->xp = 10;
		break;
	}
	case 1: {
		this->loadTexture("resources/enemies/gordo_one.png");
		this->id = "ENEMY_Urchin";
		this->scaleX *= 0.5;
		this->scaleY *= 0.5;
		//this->pivot.x = w * scaleX / 2;
		//this->pivot.y = h * scaleY / 2;
		xSpe = 3;
		ySpe = 3;
		state = 0;
		this->xBound = 512 - (w * scaleX);
		this->yBound = 384 - (h * scaleY);
		projectileDamage = 2;
		health = 200;
		this->xp = 200;
		break;
	}
	case 2: {
		this->loadTexture("resources/enemies/gordo_one.png");
		this->id = "ENEMY_Urchin";
		this->scaleX *= 0.5;
		this->scaleY *= 0.5;
		//this->pivot.x = w * scaleX / 2;
		//this->pivot.y = h * scaleY / 2;
		xSpe = 3;
		ySpe = 3;
		state = 0;
		this->xBound = 512 - (w * scaleX);
		this->yBound = 384 - (h * scaleY);
		projectileDamage = 4;
		health = 400;
		this->xp = 100;
		break;
	}
	case 3: {
		this->loadTexture("resources/enemies/gordo_one.png");
		this->id = "ENEMY_Urchin";
		this->scaleX *= 0.5;
		this->scaleY *= 0.5;
		//this->pivot.x = w * scaleX / 2;
		//this->pivot.y = h * scaleY / 2;
		xSpe = 3;
		ySpe = 3;
		state = 0;
		this->xBound = 512 - (w * scaleX);
		this->yBound = 384 - (h * scaleY);
		projectileDamage = 8;
		health = 1000;
		this->xp = 2500;
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
	restTimer++;
	if (restTimer < restTime) {
		return;
	}
	restTimer = 0;
	if (state == 0) {
		timer++;
		if (timer <= 60) {
			if (timer % 5 == 0)
				this->increaseAlpha();
		}
		if (timer > 60) {
			timer = 0;
			this->scaleX = .8;
			this->scaleY = .8;
			this->translate(-w * scaleX * .625 / 4, h * -scaleY * .625 / 4);
			//this->setHitbox(-.5, 1.5);
			std::cout << "state2 urchin" << '\n';
			state++;
			health /= 2;
		}

	} else if (state == 1) {
		if (type < 2) {
			state++;
			return;
		}
		timer++;
		if (timer % 50 == 0) {
			//Generate projectiles 
			string path = "resources/Projectiles/spikedball.png";
			int midX = this->position.x + (dstrect.w) / 3;
			int midY = this->position.y + (dstrect.h) / 3;
			Projectile *p1 = new Projectile(path, midX, midY, 0, 3, 1200, 0.25,
					0.25, projectileDamage); //down
			Projectile *p2 = new Projectile(path, midX, midY, 0, -3, 1200, 0.25,
					0.25, projectileDamage); //up
			Projectile *p3 = new Projectile(path, midX, midY, 3, 0, 1200, 0.25,
					0.25, projectileDamage); //right
			Projectile *p4 = new Projectile(path, midX, midY, -3, 0, 1200, 0.25,
					0.25, projectileDamage); // left
			Projectile *p5 = new Projectile(path, midX, midY, 2, 2, 1200, 0.25,
					0.25, projectileDamage); //down right
			Projectile *p6 = new Projectile(path, midX, midY, 2, -2, 1200, 0.25,
					0.25, projectileDamage); //up right
			Projectile *p7 = new Projectile(path, midX, midY, -2, 2, 1200, 0.25,
					0.25, projectileDamage); //down left
			Projectile *p8 = new Projectile(path, midX, midY, -2, -2, 1200,
					0.25, 0.25, projectileDamage); // up left
			((DisplayObjectContainer*) (this->parent))->addChild(p1);
			((DisplayObjectContainer*) (this->parent))->addChild(p2);
			((DisplayObjectContainer*) this->parent)->addChild(p3);
			((DisplayObjectContainer*) this->parent)->addChild(p4);
			((DisplayObjectContainer*) (this->parent))->addChild(p5);
			((DisplayObjectContainer*) (this->parent))->addChild(p6);
			((DisplayObjectContainer*) this->parent)->addChild(p7);
			((DisplayObjectContainer*) this->parent)->addChild(p8);
			DTEvent e1("OBJ_ADD", &Game::eventHandler, p1);
			Game::eventHandler.dispatchEvent(&e1);
			DTEvent e2("OBJ_ADD", &Game::eventHandler, p2);
			Game::eventHandler.dispatchEvent(&e2);
			DTEvent e3("OBJ_ADD", &Game::eventHandler, p3);
			Game::eventHandler.dispatchEvent(&e3);
			DTEvent e4("OBJ_ADD", &Game::eventHandler, p4);
			Game::eventHandler.dispatchEvent(&e4);
			DTEvent e5("OBJ_ADD", &Game::eventHandler, p5);
			Game::eventHandler.dispatchEvent(&e5);
			DTEvent e6("OBJ_ADD", &Game::eventHandler, p6);
			Game::eventHandler.dispatchEvent(&e6);
			DTEvent e7("OBJ_ADD", &Game::eventHandler, p7);
			Game::eventHandler.dispatchEvent(&e7);
			DTEvent e8("OBJ_ADD", &Game::eventHandler, p8);
			Game::eventHandler.dispatchEvent(&e8);
		}
		if (timer > 200) {
			timer = 0;
			state++;
		}
		//state++;
	} else if (state == 2) {
		timer++;
		//if (timer <= 240) {

		//}
		if (timer > 100) {
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
			health *= 2;
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
