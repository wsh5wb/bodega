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
	TweenJuggler *juggler = TweenJuggler::getInstance();


	DisplayObject * ts = new DisplayObject("titlescreen","resources/art/TitleScreen.png");
	AffineTransform at;

	//ts->setAlpha(0);
	ts->draw(at);
	//cout << "alp" << ts->getAlpha() << endl;
	SDL_RenderPresent(Game::renderer);
	Tween *tsTween = new Tween(ts);
	
	//cout << ts->w << " " << ts->h;
	while(!started && !quit){
		SDL_PollEvent(&event);
		if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.scancode == SDL_SCANCODE_SPACE){
				started = true;
				
				tsTween->animate(TWEEN_ALPHA, ts->getAlpha(), 0, 30, TWEEN_LINEAR,EASE_OUT);

				juggler->add(tsTween);

				while(!tsTween->isComplete()){
					SDL_RenderClear(Game::renderer);
					juggler->nextFrame();
					ts->draw(at);
					SDL_RenderPresent(Game::renderer);
				}
				myGame->start();
			}
		} else if(event.type == SDL_CONTROLLERBUTTONDOWN){
			if(event.cbutton.button == SDL_CONTROLLER_BUTTON_START){
				started = true;
				tsTween->animate(TWEEN_ALPHA, ts->getAlpha(), 0, 30, TWEEN_LINEAR,EASE_OUT);
				juggler->add(tsTween);

				while(!tsTween->isComplete()){
					SDL_RenderClear(Game::renderer);
					juggler->nextFrame();

					ts->draw(at);
					SDL_RenderPresent(Game::renderer);
				}
				myGame->start();
			}
		}
		if(event.type == SDL_QUIT){
			quit = true;
		}

	}

	//myGame->loadTexture("resources/art/TitleScreen.png");
	//myGame->start();
	//if(texture != NULL) SDL_DestroyTexture(texture);
	delete tsTween;
	delete ts;
	delete myGame;
	return 0;
}