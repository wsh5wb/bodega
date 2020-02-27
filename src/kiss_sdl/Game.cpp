#include <iostream>
#include "Game.h"
#include <string>
#include <ctime>
#include "DisplayObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <typeinfo>

using namespace std;

SDL_Renderer* Game::renderer;
kiss_window* Game::window;
Game* Game::instance;
unsigned int Game::frameCounter = 0;

Game::Game(int windowWidth, int windowHeight){
	Game::instance = this;
	
	//this->windowWidth = windowWidth;
	//this->windowHeight = windowHeight;
	
	kiss_window_new(window,NULL,1,0,0,1200,1000);
	window->visible = 1;
	initSDL();
	TTF_Init();
	// cout << Game::renderer << endl;
	mouse = new Mouse("Mouse",100,100,100);
	mouse->makeInvisible();
	mouse->setAlpha(80);
	Game::window = window;
}

Game::~Game(){
	// delete mouse;
	quitSDL();
}

void Game::quitSDL(){
	cout << "Quitting sdl" << endl;
	kiss_clean(&objects);
	SDL_DestroyRenderer(Game::renderer);
	//SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();
}

void Game::initSDL(){
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	//window = SDL_CreateWindow("myGame",
		//SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowWidth, this->windowHeight, 0);

	//SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Renderer * renderer = kiss_init("My Game",&objects,1200,1000);
	Game::renderer = renderer;
	
}

void Game::start(){

	int ms_per_frame = (1.0/(double)this->frames_per_sec)*1000;
	std::clock_t start = std::clock();

	bool quit = false;
	SDL_Event event;

	while(!quit){
		std::clock_t end = std::clock();
		double duration = (( end - start ) / (double) CLOCKS_PER_SEC)*1000;
		if(duration > ms_per_frame){
			start = end;
			this->update(pressedKeys);
			AffineTransform at;
			this->draw(at);
		}

		SDL_PollEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				pressedKeys.insert(event.key.keysym.scancode);
				break;
			case SDL_KEYUP:
				pressedKeys.erase(event.key.keysym.scancode);
				break;
		}

		mouse->setState(event.type, event);
	
	}
}

void Game::update(set<SDL_Scancode> pressedKeys){
	frameCounter++;
}
void Game::draw(AffineTransform &at){
}