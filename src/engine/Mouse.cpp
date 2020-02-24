#include "Mouse.h"
#include "Game.h"
#include <iostream>

using namespace std;

Mouse::Mouse() : DisplayObject(){
 	mouseCoords = {0,0};
	leftClickCoords = {0,0};
	leftClick = false;
	rightClick = false;
	isMoving = false;
	vis = false;
}

Mouse::Mouse(string id, int red, int green, int blue) : DisplayObject(id, red, green, blue){
	mouseCoords = {0,0};
	leftClickCoords = {0,0};
	leftClick = false;
	rightClick = false;
	isMoving = false;
	vis = false;
}

Mouse::~Mouse(){

}

SDL_Point Mouse::getCoordinates(){
	return this->mouseCoords;
}

void Mouse::setState(Uint32 eventType, SDL_Event event){
	if (eventType == SDL_MOUSEBUTTONUP){
		if (event.button.button == SDL_BUTTON_LEFT && this->leftClick) {
	        this->leftClick = false;
	        makeInvisible();
	    }

	    if(event.button.button == SDL_BUTTON_RIGHT){
	    	this->rightClick = false;
	    }

	}
	else if (eventType == SDL_MOUSEBUTTONDOWN){
		if ( event.button.button == SDL_BUTTON_LEFT && !this->leftClick ) {
	        this->leftClick = true;
	        // get starting mouse coordinates
	        SDL_GetMouseState( &this->leftClickCoords.x, &this->leftClickCoords.y );
	        makeVisible();
	    }

	    if (event.button.button == SDL_BUTTON_RIGHT && !this->rightClick) {
	        this->rightClick = true;
	        // SDL_GetMouseState( &this->start_coords.x, &this->start_coords.y );
    	}
	}

    if ( eventType == SDL_MOUSEMOTION ) {
        this->isMoving = true;
        this->mouseCoords.x = event.motion.x;
        this->mouseCoords.y = event.motion.y;
    } else {
        this->isMoving = false;
    }

}

void Mouse::update(set<SDL_Scancode> pressedKeys){
	DisplayObject::update(pressedKeys);

}

void Mouse::draw(AffineTransform &at){
	if(!vis)	return;

	w = this->mouseCoords.x - this->leftClickCoords.x;
	h = this->mouseCoords.y - this->leftClickCoords.y;

	SDL_Point tl = this->leftClickCoords;
	SDL_Point pOrigin = {0,0};
	if(w > 0 && h < 0){
		h *= -1;
		tl.y -= h; 
	}
	else if (w < 0 && h > 0){
		w *= -1;
		tl.x -= w;
	}
	else if (w < 0 && h < 0){
		w *= -1; h *= -1;
		tl.x -= w; tl.y -= h;
	}

	SDL_Rect dstrect = {tl.x, tl.y, w, h};

	// cout << getCurTexture() << endl;
	SDL_RenderCopyEx(Game::renderer, curTexture, NULL, &dstrect, 0, &pOrigin, SDL_FLIP_NONE);
}
