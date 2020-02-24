#ifndef MOUSE_H
#define MOUSE_H
#include "DisplayObject.h"
#include <SDL2/SDL.h>
// inspired by 
// https://stackoverflow.com/questions/29735309/c-sdl-draw-dynamic-rect-based-on-mouse-position
class Mouse : public DisplayObject{
public:
	Mouse();
	Mouse(string id, int red, int green, int blue);
	~Mouse();
	SDL_Point getCoordinates();
	void setState(Uint32 eventType, SDL_Event event);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

private:
	SDL_Point mouseCoords;
	SDL_Point leftClickCoords;
	bool leftClick;
	bool rightClick;
	bool isMoving;
};

#endif