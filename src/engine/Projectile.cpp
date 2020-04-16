#include "Projectile.h"

Projectile::Projectile() : Sprite(){
	
}


/*Projectile::Projectile(string id, string path) : Sprite(id,path,true){

}*/

Projectile::Projectile(string path, int x, int y, int speedX, int speedY, int timeout, double scaleX, double scaleY) : Sprite("projectile",path){
	this->speedX = speedX;
	this->speedY = speedY;
	this->timeout = timeout;
	this->setScale(scaleX,scaleY);
	this->moveTo(x, y);
	this->start = std::clock();
}

/*Projectile::Projectile(string path, int x, int y, int lowX, int highX, int lowY, int highY, int timeout, double scaleX, double scaleY) : Sprite("particle",path,true){
	this->lowX = lowX;
	this->speedX = highX;
	this->lowY = lowY;
	this->speedY = highY;
	this->timeout = timeout;
	this->setScale(scaleX,scaleY);
	this->moveTo(x, y);
	this->start = std::clock();
	rand = true;
}*/


void Projectile::update(set<SDL_Scancode> pressedKeys){
	position.x += speedX;
	position.y += speedY;
}
