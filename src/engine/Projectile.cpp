#include "Projectile.h"

Projectile::Projectile() : Sprite(){
	
}


/*Projectile::Projectile(string id, string path) : Sprite(id,path,true){

}*/

Projectile::Projectile(string path, int x, int y, int speedX, int speedY, int timeout, double scaleX, double scaleY) : Sprite("CHAR_PROJECTILE",path){
	/*if(speedX != 0 && speedY != 0){
		if(speedX < 0){speedX = -sqrt(-1*speedX);}
		else {speedX = sqrt(speedX);}
		
		if(speedY < 0){speedY = -sqrt(-1*speedY);}
		else{speedY = sqrt(speedY);}
	}*/

	this->speedX = speedX;
	this->speedY = speedY;

	this->rotate(atan2(speedY,speedX));
	
	this->timeout = timeout;
	this->setScale(scaleX,scaleY);
	this->moveTo(x, y);
	this->start = std::clock();
	setHitbox(0.05,0.95);
	this->showHitbox = true;
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

	// TODO: If we get strange behavior rarely, fix this :)
	if((((std::clock() - start ) / (double) CLOCKS_PER_SEC)*1000) > timeout){
		((DisplayObjectContainer*)this->parent)->removeImmediateChild(this);
	}
}
