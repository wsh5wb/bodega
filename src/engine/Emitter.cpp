#include "Emitter.h"
#include <iostream>

Emitter::Emitter() : Sprite(){
	/*image = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
	SDL_FillRect(image, NULL, SDL_MapRGB(image->format, 0, 0, 0));
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
	setTexture(texture);*/
	loadRGBTexture(100,0,0);
	alpha = 0;
	w = 100; h = 100;
}

Emitter::Emitter(int w, int h, bool play) : Sprite(){
	loadRGBTexture(0,0,0,w,h);
	alpha = 0;
	this->w = w;
	this->h = h;
	playing = play;
}

Emitter::Emitter(string id, string filepath, bool play) : Sprite(id,filepath,false){
	playing = play;
}

Emitter::~Emitter(){
	for(vector<Particle*>::iterator it = particles.begin(); it != particles.end();it++){
		delete *it;
	}particles.clear();

	for(vector<Particle*>::iterator it = particleType.begin(); it != particleType.end();it++){
		delete *it;
	}particles.clear();
}

void Emitter::addParticle(string path, int speedX, int speedY, int timeout, int generateTime, double scaleX, double scaleY){
	Particle * p = new Particle(path,0,0,speedX,speedY,timeout,scaleX,scaleY);
	p->generateTime = generateTime;
	particleType.push_back(p);
}

void Emitter::addRandParticle(string path, int xLow, int xHigh, int yLow, int yHigh, int timeout, int generateTime, double scaleX, double scaleY){
	Particle * p = new Particle(path,0,0,xLow,xHigh,yLow,yHigh,timeout,scaleX,scaleY);
	p->generateTime = generateTime;
	particleType.push_back(p);
}

void Emitter::start(){
	playing = true;
}

void Emitter::stop(){
	playing = false;
}

void Emitter::update(set<SDL_Scancode> pressedKeys){
	//std::clock_t end = 
	for(vector<Particle*>::iterator it = particles.begin(); it != particles.end();){
		Particle * p = *it;
		if((((std::clock() - p->start ) / (double) CLOCKS_PER_SEC)*1000) > p->timeout){
			it = particles.erase(it);
			delete p;
		}else{
			p->update(pressedKeys);
			it++;
		}

	}

	if(playing){
		for(Particle *p : particleType){
			if((((std::clock() - p->start ) / (double) CLOCKS_PER_SEC)*1000) > p->generateTime){
				p->start = std::clock();
				Particle * n;
				if(p->rand){
					int randX = (rand() % (p->speedX - p->lowX + 1)) + p->lowX;
					int randY = (rand() % (p->speedY - p->lowY + 1)) + p->lowY;
					n = new Particle(p->imgPath,rand() % w, rand() % h, randX, randY,p->timeout,p->scaleX,p->scaleY);
				}else{
					n = new Particle(p->imgPath,rand() % w, rand() % h, p->speedX,p->speedY,p->timeout,p->scaleX,p->scaleY);
				}
				particles.push_back(n);
			}
		}
	}
}

void Emitter::draw(AffineTransform &at){
	DisplayObject::draw(at);
	DisplayObject::applyTransformations(at);

	for(Particle* p : particles){
		p->draw(at);
	}
	
	DisplayObject::reverseTransformations(at);	
}