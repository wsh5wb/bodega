#ifndef DEVLOOP_H
#define DEVLOOP_H

#include <vector>
#include <set>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ItemBar.h"
#include "definitions.h"
#include "../kiss/kiss_sdl.h"
#include "../../src/engine/DisplayObjectContainer.h"
#include "../../src/engine/Mouse.h"
#include "../../src/engine/Camera.h"

using namespace std;

class DevLoop : public DisplayObjectContainer{

public:

	/* Singleton pattern */
	static DevLoop* instance;

	int frames_per_sec = 60;
	int windowWidth, windowHeight;

	// SDL_Window * window;

	static SDL_Renderer* renderer;

	kiss_array objects, a1;
	kiss_entry xPosEntry = {0};
	ItemBar* infoBar;

	kiss_window window1, sprite_bar, char_attributes_bar, editor_window;

	//Global frame counter
	static unsigned int frameCounter;

	DevLoop(int windowWidth, int windowHeight);
	virtual ~DevLoop();
	void start();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	Mouse* mouse;
	bool disable_input;	
	
	double gridSize;
	bool gridOn = true;
private:

	void initSDL();
	void quitSDL();
	set<SDL_Scancode> pressedKeys;

};

#endif