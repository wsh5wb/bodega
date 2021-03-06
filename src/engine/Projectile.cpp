#include "Projectile.h"

Projectile::Projectile() : AnimatedSprite(){

}

Projectile::Projectile(int my_type, int x, int y, int speedX, int speedY, int timeout, double scaleX, double scaleY) : AnimatedSprite("CHAR_PROJECTILE"){

	this->my_type = my_type;
	this->speedX = speedX;
	this->speedY = speedY;
	this->addAnimation("resources/Projectiles/Bblue.png",
			"resources/Projectiles/Bblue.xml", "Blue", 5, 45, true);
	this->addAnimation("resources/Projectiles/redB.png",
			"resources/Projectiles/redB.xml", "Red", 5, 45, true);
	this->addAnimation("resources/Projectiles/Bpink.png",
			"resources/Projectiles/Bpink.xml", "Pink", 5, 45, true);
	if (this->my_type == 1){
		play("Red");
	}else if(this->my_type == 2){
		play("Blue");
	}else{
		play("Pink");
	}
	this->rotate(atan2(speedY,speedX));
	this->damage = 100;
	this->timeout = timeout;
	this->setScale(scaleX,scaleY);
	this->moveTo(x, y);
	this->start = std::clock();
	setHitbox(0.05,0.95);
	// this->showHitbox = true;
}

Projectile::Projectile(string path, int x, int y, int speedX, int speedY, int timeout, double scaleX, double scaleY, int damage) : AnimatedSprite("EN_PROJECTILE",path){
	this->speedX = speedX;
	this->speedY = speedY;
	this->my_type = 4;
	this->rotate(PI/6-atan2(speedY,speedX));
	this->timeout = timeout;
	this->setScale(scaleX,scaleY);
	this->moveTo(x, y);
	this->start = std::clock();
	this->damage = damage;
	setHitbox(0.05,0.95);
	//this->showHitbox = true;
}

int Projectile::getDamage(){
	return damage;
}

Projectile::~Projectile(){

}

int Projectile::getMyType(){
	return this->my_type;
}
void Projectile::draw(AffineTransform &at) {
	AnimatedSprite::draw(at);
}

void Projectile::update(set<SDL_Scancode> pressedKeys){
	AnimatedSprite::update(pressedKeys);
	position.x += speedX;
	position.y += speedY;

	// TODO: If we get strange behavior rarely, fix this :)
	if((((std::clock() - start ) / (double) CLOCKS_PER_SEC)*1000) > timeout){
		((DisplayObjectContainer*)this->parent)->removeImmediateChild(this);
	}
}
