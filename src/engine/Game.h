#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayObjectContainer.h"
#include "Mouse.h"
#include <vector>
#include <set>

using namespace std;

class Game : public DisplayObjectContainer{

public:

	/* Singleton pattern */
	static Game* instance;

	int frames_per_sec = 60;
	int windowWidth, windowHeight;

	SDL_Window * window;
	static SDL_Renderer* renderer;

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

	const int JOYSTICK_DEAD_ZONE = 8000;
	SDL_Joystick* gGameController = NULL;
};

#endif