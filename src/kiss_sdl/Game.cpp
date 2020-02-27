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

Game* Game::instance;
unsigned int Game::frameCounter = 0;

Game::Game(int windowWidth, int windowHeight){
	Game::instance = this;
	
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	// initSDL();
	// TTF_Init();
	SDL_Renderer * renderer = kiss_init("dev_tool", &objects, 1200, 1000);
	if(!renderer){
		cout << "renderer failed to init" << endl;
		return; 
	}

	Game::renderer = renderer; 

	kiss_array_new(&a1);
	kiss_array_append(&objects, ARRAY_TYPE, &a1);

	// cout << Game::renderer << endl;
	mouse = new Mouse("Mouse",100,100,100);
	mouse->makeInvisible();
	mouse->setAlpha(80);

}

Game::~Game(){
	// delete mouse;
	quitSDL();
}

void Game::quitSDL(){
	cout << "Quitting sdl" << endl;
	kiss_clean(&objects);
	SDL_DestroyRenderer(Game::renderer);

	// SDL_DestroyWindow(window);


	IMG_Quit();
	SDL_Quit();
}

void Game::initSDL(){
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	// window = SDL_CreateWindow("myGame",
	// 	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowWidth, this->windowHeight, 0);

	// SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	//SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Renderer * renderer = kiss_init("My Game",&objects,1200,1000);
	Game::renderer = renderer;
	
}

void Game::start(){

	kiss_textbox textbox1 = {0};
	kiss_entry entry = {0};
	int textbox_width, textbox_height, draw;
	draw = 1;
	textbox_width = 200;
	textbox_height = 100;

	kiss_window_new(&window, NULL, 1, 0, 0, kiss_screen_width,
		kiss_screen_height);
	kiss_textbox_new(&textbox1, &window, 1, &a1, kiss_screen_width / 2 -
		(2 * textbox_width + 2 * kiss_up.w - kiss_edge) / 2,
		3 * kiss_normal.h, textbox_width, textbox_height);

	window.visible = 1;

	int ms_per_frame = (1.0/(double)this->frames_per_sec)*1000;
	std::clock_t start = std::clock();

	bool quit = false;
	SDL_Event event;

	while(!quit){

		SDL_PollEvent(&event);
		kiss_window_event(&window, &event, &draw);
		kiss_entry_event(&entry, &event, &draw);
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

		SDL_RenderClear(renderer);

		std::clock_t end = std::clock();
		double duration = (( end - start ) / (double) CLOCKS_PER_SEC)*1000;

		if(duration > ms_per_frame){
			start = end;
			this->update(pressedKeys);
			AffineTransform at;
			this->draw(at);
		}

		kiss_textbox_draw(&textbox1, renderer);

		SDL_RenderPresent(renderer);
	}
}

void Game::update(set<SDL_Scancode> pressedKeys){
	frameCounter++;
}
void Game::draw(AffineTransform &at){
}