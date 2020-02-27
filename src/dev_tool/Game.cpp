#include <iostream>
#include "Game.h"
#include <string>
#include <ctime>
#include "DisplayObject.h"
#include "SceneWindow.h"
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
	int windowH = 800;
	// initSDL();
	// TTF_Init();

	SDL_Renderer * renderer = kiss_init("dev_tool", &objects, 1280, 720);

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
	//SDL_Renderer * renderer = kiss_init("My Game",&objects,1200,1000);
	Game::renderer = renderer;
	
}

void Game::start(){

	int textbox_width, textbox_height, draw;
	draw = 1;
	textbox_width = 200;
	textbox_height = 100;

	// kiss_window_new(&window, NULL, 1, 0, 0, kiss_screen_width,
	// 	kiss_screen_height);
	SDL_Color darkGrey = {64,64,64};
	//kiss_window_new(&sprite_bar, NULL, 1, 0,kiss_screen_height*3/4, kiss_screen_width, 
	//	kiss_screen_height/4);
	kiss_window_new(&char_attributes_bar, NULL, 1, kiss_screen_width*4/5, 0, kiss_screen_width/5, 
		kiss_screen_height);

	//kiss_entry_new(&xPosEntry,&char_attributes_bar,0,"xPos:",kiss_screen_width*4/5 + 20,20,60);
	
	char_attributes_bar.bg = darkGrey; sprite_bar.bg = darkGrey;
	infoBar = ItemBar(&char_attributes_bar);

	kiss_window_new(&dir_window, NULL, 1, 
		kiss_screen_width / 2 - 300 / 2, 
		kiss_screen_height / 2- 300 / 2, 300, 300);

	SceneWindow scene_window(kiss_screen_width, kiss_screen_height);

	//sprite_bar.visible = 1;
	char_attributes_bar.visible = 1;
	dir_window.visible = 0;

	bool quit = false;
	SDL_Event event;

	int ms_per_frame = (1.0/(double)this->frames_per_sec)*1000;
	std::clock_t start = std::clock();

	while(!quit){

		while(SDL_PollEvent(&event)){

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

			//kiss_window_event(&sprite_bar, &event, &draw);
			kiss_window_event(&char_attributes_bar, &event, &draw);
			kiss_window_event(&dir_window, &event, &draw);
			infoBar.event(&event,&draw);
			//kiss_entry_event(&xPosEntry,&event,&draw);

			scene_window.event(&event, &draw, window1, dir_window);

			mouse->setState(event.type, event);
		}

		SDL_RenderClear(renderer);

		std::clock_t end = std::clock();
		double duration = (( end - start ) / (double) CLOCKS_PER_SEC)*1000;

		if(duration > ms_per_frame){
			start = end;
		}

		
		scene_window.draw(renderer);


		// Do all scene drawing between the above renderer and next kiss_draws
		this->update(pressedKeys);
		AffineTransform at;
		this->draw(at);

		//kiss_window_draw(&sprite_bar, renderer);
		kiss_window_draw(&char_attributes_bar, renderer);
		kiss_window_draw(&dir_window, renderer);
		infoBar.draw(renderer);
		//kiss_entry_draw(&xPosEntry,renderer);
		
		SDL_RenderPresent(renderer);

	}
}

void Game::update(set<SDL_Scancode> pressedKeys){
	frameCounter++;
}
void Game::draw(AffineTransform &at){
}
