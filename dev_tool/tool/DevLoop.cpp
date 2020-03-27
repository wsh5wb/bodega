#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <typeinfo>
#include <iostream>
#include <string>
#include <ctime>
#include "DevLoop.h"
#include "FileBrowser.h"
#include "../../src/engine/DisplayObject.h"

using namespace std;

SDL_Renderer* DevLoop::renderer;

DevLoop* DevLoop::instance;
unsigned int DevLoop::frameCounter = 0;

DevLoop::DevLoop(int windowWidth, int windowHeight){
	DevLoop::instance = this;
	
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	int windowH = 800;

	SDL_Renderer * renderer = kiss_init("dev_tool", &objects, 1280, 720);

	if(!renderer){
		cout << "renderer failed to init" << endl;
		return; 
	}

	DevLoop::renderer = renderer;
	this->renderer = renderer;

	infoBar = new ItemBar(&char_attributes_bar);
	// cout << DevLoop::renderer << endl;
	mouse = new Mouse("Mouse",100,100,100);
	mouse->makeInvisible();
	mouse->setAlpha(80);
	mouse->setRenderer(DevLoop::renderer);
	disable_input = false;
}

DevLoop::~DevLoop(){
	// delete mouse;
	quitSDL();
}

void DevLoop::quitSDL(){
	cout << "Quitting sdl" << endl;
	kiss_clean(&objects);
	SDL_DestroyRenderer(DevLoop::renderer);

	// SDL_DestroyWindow(window);


	IMG_Quit();
	SDL_Quit();
}

void DevLoop::initSDL(){
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	// window = SDL_CreateWindow("myDevLoop",
	// 	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowWidth, this->windowHeight, 0);

	// SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	//SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	//SDL_Renderer * renderer = kiss_init("My DevLoop",&objects,1200,1000);
	DevLoop::renderer = renderer;
	
}

void DevLoop::start(){

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
	

	kiss_window_new(&editor_window,NULL,1, 0,0, kiss_screen_width, kiss_screen_height);
	editor_window.bg = kiss_black;
	FileBrowser scene_window(objects, 640, 480, kiss_screen_width, kiss_screen_height, 
		&editor_window, this);

	//sprite_bar.visible = 1;
	char_attributes_bar.visible = 1;
	editor_window.visible = 1;

	bool quit = false;
	SDL_Event event;

	int ms_per_frame = (1.0/(double)this->frames_per_sec)*1000;
	std::clock_t start = std::clock();

	while(!quit){
		SDL_Delay(10);
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

			infoBar->event(&event,&draw);
			//kiss_entry_event(&xPosEntry,&event,&draw);

			// scene_window.event(&event, &draw, window1, dir_window);
			scene_window.event(&event, &draw);
			kiss_window_event(&editor_window, &event, &draw);


			mouse->setState(event.type, event);
		}

		SDL_RenderClear(renderer);

		std::clock_t end = std::clock();
		double duration = (( end - start ) / (double) CLOCKS_PER_SEC)*1000;

		if(duration > ms_per_frame){
			start = end;
		}

		// Do all scene drawing between the above renderer and next kiss_draws
		this->update(pressedKeys);
		AffineTransform at;

		kiss_window_draw(&editor_window, renderer);
		this->draw(at);

		//kiss_window_draw(&sprite_bar, renderer);
		kiss_window_draw(&char_attributes_bar, renderer);

		infoBar->draw(renderer);
		//kiss_entry_draw(&xPosEntry,renderer);

		scene_window.draw_items(renderer);
		
		SDL_RenderPresent(renderer);

	}
}

void DevLoop::update(set<SDL_Scancode> pressedKeys){
	frameCounter++;
}

void DevLoop::draw(AffineTransform &at){
}