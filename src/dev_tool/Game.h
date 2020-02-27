#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "ItemBar.h"
#include "Mouse.h"
#include "kiss_sdl.h"
#include <vector>
#include <set>

using namespace std;

class Game : public DisplayObjectContainer{

public:

	/* Singleton pattern */
	static Game* instance;

	int frames_per_sec = 60;
	int windowWidth, windowHeight;

	// SDL_Window * window;

	static SDL_Renderer* renderer;

	kiss_array objects, a1;
	kiss_entry xPosEntry = {0};
	ItemBar infoBar;

	kiss_window window1, sprite_bar, char_attributes_bar, editor_window;

	//Global frame counter
	static unsigned int frameCounter;

	Game(int windowWidth, int windowHeight);
	virtual ~Game();
	void start();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	Mouse* mouse;
private:

	void initSDL();
	void quitSDL();
	set<SDL_Scancode> pressedKeys;


};

#endif