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
CollisionSystem Game::cs;
EventDispatcher Game::eventHandler;

Game::Game(int windowWidth, int windowHeight){
	Game::instance = this;

	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	initSDL();
	TTF_Init();
	// cout << Game::renderer << endl;
}

Game::~Game(){
	// delete mouse;
	quitSDL();
}

void Game::quitSDL(){
	cout << "Quitting sdl" << endl;

	//Close game controller
    SDL_JoystickClose( gGameController );
    gGameController = NULL;

	SDL_DestroyRenderer(Game::renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();
}

void Game::initSDL(){

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
		cout << "Failed to init SDL, Error: " << SDL_GetError() << endl;
  
  if(SDL_Init(SDL_INIT_AUDIO) < 0)
    cout << "Failed to init audio, Error: " << SDL_GetError() << endl;

	IMG_Init(IMG_INIT_PNG);

	 //Check for joysticks
    if( SDL_NumJoysticks() >= 1 ){
        //Load joystick
        gGameController = SDL_JoystickOpen( 0 );
        if( gGameController == NULL )
        	cout << "Could not initialize controller" << endl;
    }

	window = SDL_CreateWindow("myGame",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowWidth, this->windowHeight, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

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
			case SDL_JOYAXISMOTION:
				if(event.jaxis.which == 0){
					//x axis motion
					if(event.jaxis.axis == 0){
						if(event.jaxis.value < -JOYSTICK_DEAD_ZONE)
							pressedKeys.insert(SDL_SCANCODE_A);
						else if(event.jaxis.value >= -JOYSTICK_DEAD_ZONE && event.jaxis.value < 0)
							pressedKeys.erase(SDL_SCANCODE_A);
						else if(event.jaxis.value > JOYSTICK_DEAD_ZONE)
							pressedKeys.insert(SDL_SCANCODE_D);
						else if(event.jaxis.value <= JOYSTICK_DEAD_ZONE && event.jaxis.value >= 0)
							pressedKeys.erase(SDL_SCANCODE_D);
					}
					if(event.jaxis.axis == 1){
						if(event.jaxis.value < -JOYSTICK_DEAD_ZONE)
							pressedKeys.insert(SDL_SCANCODE_S);
						else if(event.jaxis.value >= -JOYSTICK_DEAD_ZONE && event.jaxis.value < 0)
							pressedKeys.erase(SDL_SCANCODE_S);
						else if(event.jaxis.value > JOYSTICK_DEAD_ZONE)
							pressedKeys.insert(SDL_SCANCODE_W);
						else if(event.jaxis.value <= JOYSTICK_DEAD_ZONE && event.jaxis.value >= 0)
							pressedKeys.erase(SDL_SCANCODE_W);
					}
				}
				break;
			case SDL_CONTROLLERBUTTONDOWN:
				switch(event.cbutton.button){
					case SDL_CONTROLLER_BUTTON_DPAD_UP:
						pressedKeys.insert(SDL_SCANCODE_W);
						break;
					case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
						pressedKeys.insert(SDL_SCANCODE_S);
						break;
					case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
						pressedKeys.insert(SDL_SCANCODE_D);
						break;
					case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
						pressedKeys.insert(SDL_SCANCODE_A);
						break;
					case SDL_CONTROLLER_BUTTON_A:
						pressedKeys.insert(SDL_SCANCODE_SPACE);
						break;
				}
				break;
			case SDL_CONTROLLERBUTTONUP:
				switch(event.cbutton.button){
					case SDL_CONTROLLER_BUTTON_DPAD_UP:
						pressedKeys.erase(SDL_SCANCODE_W);
						break;
					case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
						pressedKeys.erase(SDL_SCANCODE_S);
						break;
					case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
						pressedKeys.erase(SDL_SCANCODE_D);
						break;
					case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
						pressedKeys.erase(SDL_SCANCODE_A);
						break;
					case SDL_CONTROLLER_BUTTON_A:
						pressedKeys.erase(SDL_SCANCODE_SPACE);
						break;
				}
				break;
		}

	}
}

void Game::update(set<SDL_Scancode> pressedKeys){
	frameCounter++;
}
void Game::draw(AffineTransform &at){
}
