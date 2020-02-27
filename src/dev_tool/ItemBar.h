#ifndef ITEMBAR_H
#define ITEMBAR_H

#include "kiss_sdl.h"
#include "DisplayObjectContainer.h"
//#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class ItemBar {//public DisplayObjectContainer {
public:
	ItemBar();
	ItemBar(kiss_window * wdw);
	~ItemBar();
	//virtual void update(set<SDL_Scancode> pressedKeys);
	//virtual void draw(AffineTransform &at);
	void event(SDL_Event *event, int* draw);
	void draw(SDL_Renderer *renderer);
	kiss_window * window = {0};
private:
	//DisplayObject* draggable = NULL;
	kiss_entry xPosEntry = {0};
	kiss_label xPosLabel = {0};

};

#endif