#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <DisplayObject.h>
#include <iostream>
#include "MyGame.h"

using namespace std;

int main(int argc, char ** argv)
{
	MyGame* myGame = new MyGame();

	bool started = false, quit = false;
	SDL_Event event;
	DisplayObject * ts = new DisplayObject("titlescreen","resources/art/TitleScreen.png");
	//myGame->loadTexture("resources/art/TitleScreen.png");
	AffineTransform at;
	ts->draw(at);
	SDL_RenderPresent(Game::renderer);
	cout << ts->w << " " << ts->h;
	while(!started && !quit){
		SDL_PollEvent(&event);
		if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.scancode == SDL_SCANCODE_SPACE){
				started = true;
				myGame->start();
			}
		} else if(event.type == SDL_CONTROLLERBUTTONDOWN){
			if(event.cbutton.button == SDL_CONTROLLER_BUTTON_START){
				started = true;
				myGame->start();
			}
		}
		if(event.type == SDL_QUIT){
			quit = true;
		}

	}
	//myGame->start();
	//if(texture != NULL) SDL_DestroyTexture(texture);
	delete ts;
	delete myGame;
	return 0;
}