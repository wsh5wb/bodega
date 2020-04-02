#include "Particle.h"

Particle::Particle() : Sprite(){
	
}

Particle::Particle(int red, int green, int blue, int w, int h) : Sprite(){
	loadRGBTexture(red,green,blue,w,h);
	this->w = w;
	this->h = h;
}

Particle::Particle(string id, string path) : Sprite(id,path,true){

}

Particle::Particle(string path, int x, int y, int speedX, int speedY, int timeout, double scaleX, double scaleY) : Sprite("particle",path,true){
	this->speedX = speedX;
	this->speedY = speedY;
	this->timeout = timeout;
	this->setScale(scaleX,scaleY);
	this->moveTo(x, y);
	this->start = std::clock();
	rand = false;
}

Particle::Particle(string path, int x, int y, int lowX, int highX, int lowY, int highY, int timeout, double scaleX, double scaleY) : Sprite("particle",path,true){
	this->lowX = lowX;
	this->speedX = highX;
	this->lowY = lowY;
	this->speedY = highY;
	this->timeout = timeout;
	this->setScale(scaleX,scaleY);
	this->moveTo(x, y);
	this->start = std::clock();
	rand = true;
}


void Particle::update(set<SDL_Scancode> pressedKeys){
	position.x += speedX;
	position.y += speedY;
}


/*void Pertical::draw(AffineTransform &at){
	applyTransformations(at);

	SDL_SetRenderDrawColor(Game::renderer,255,255,255,255);
	SDL_RenderFillRect(Game::renderer,)

	SDL_SetRenderDrawColor(Game::renderer,0,0,0,255);
	
	reverseTransformations(at);	
}*/