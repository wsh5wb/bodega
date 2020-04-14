#ifndef MOUSE_H
#define MOUSE_H
#include "DisplayObjectContainer.h"
#include <SDL2/SDL.h>
// inspired by 
// https://stackoverflow.com/questions/29735309/c-sdl-draw-dynamic-rect-based-on-mouse-position
class Mouse : public DisplayObjectContainer{
public:
	Mouse();
	Mouse(string id, int red, int green, int blue);
	~Mouse();
	SDL_Point getCoordinates();
	SDL_Point getGlobalCoordinates();
	void setState(Uint32 eventType, const SDL_Event &event);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	bool leftClick;
	bool rightClick;
	bool isMoving;
	bool isScrolling;
	bool wheelUp;
	bool wheelDown;

private:
	SDL_Point mouseCoords;
	SDL_Point leftClickCoords;
	
};

#endif