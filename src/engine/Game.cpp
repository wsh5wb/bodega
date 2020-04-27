#include <iostream>
#include "Game.h"
#include <string>
#include <ctime>
#include "DisplayObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <typeinfo>

using namespace std;

SDL_Renderer* Game::renderer;
Game* Game::instance;
unsigned int Game::frameCounter = 0;
CollisionSystem* Game::cs;
EventDispatcher Game::eventHandler;

Game::Game(int windowWidth, int windowHeight){
	Game::instance = this;
	Game::cs = new CollisionSystem();

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
    SDL_GameControllerClose( gGameController );
    gGameController = NULL;

	SDL_DestroyRenderer(Game::renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::initSDL(){

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
		cout << "Failed to init SDL, Error: " << SDL_GetError() << endl;

  if(SDL_Init(SDL_INIT_AUDIO) < 0)
    cout << "Failed to init audio, Error: " << SDL_GetError() << endl;

	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		cout <<"Failed to init mixer, Error: " << Mix_GetError() <<endl;

	IMG_Init(IMG_INIT_PNG);

	if(TTF_Init() == -1){
		std::cerr<< "Failed to initialize SDL_ttf. \n";
	}
	 //Check for joysticks
    if( SDL_NumJoysticks() >= 1 ){
        //Load joystick
    	fprintf(stderr, "NUMJOYSTICKS %d\n", SDL_NumJoysticks());
        gGameController = SDL_GameControllerOpen(0);
        if( gGameController == NULL )
        	fprintf(stderr, "Game controller failed to init (controller is NULL/incompatible)");
    }

	window = SDL_CreateWindow("myGame",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowWidth, this->windowHeight, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	Game::renderer = renderer;
}

void Game::start(){

	int ms_per_frame = (1.0/(double)this->frames_per_sec)*1000;
	std::clock_t start = std::clock();

	quit = false; 
	paused = false;
	won = false;
	mapMode = false;
	SDL_Event event;
	DisplayObject * ps = NULL, *ws = NULL;

	while(!quit){
		if(!paused){
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
					if(event.key.keysym.scancode == SDL_SCANCODE_P){
						paused = true;
						ps = new DisplayObject("pausescreen","resources/art/GamePaused.png");
						//myGame->loadTexture("resources/art/TitleScreen.png");
						AffineTransform at;
						ps->draw(at);
						SDL_RenderPresent(Game::renderer);

						break;
					}
					pressedKeys.insert(event.key.keysym.scancode);
					break;
				case SDL_KEYUP:
					pressedKeys.erase(event.key.keysym.scancode);
					break;
				case SDL_JOYAXISMOTION:
					if(event.jaxis.which == 0){
						//x axis motion
						if(event.jaxis.axis == 0){
							printf("X value is: %d\n", event.jaxis.value);
							if(event.jaxis.value < -JOYSTICK_DEAD_ZONE)
								pressedKeys.insert(SDL_SCANCODE_A);
							else if(event.jaxis.value > JOYSTICK_DEAD_ZONE)
								pressedKeys.insert(SDL_SCANCODE_D);
							if(event.jaxis.value >= -JOYSTICK_DEAD_ZONE && event.jaxis.value <= 0)
								pressedKeys.erase(SDL_SCANCODE_A);
							if(event.jaxis.value <= JOYSTICK_DEAD_ZONE && event.jaxis.value >= 0)
								pressedKeys.erase(SDL_SCANCODE_D);
						}
						if(event.jaxis.axis == 1){
							if(event.jaxis.value < -JOYSTICK_DEAD_ZONE)
								pressedKeys.insert(SDL_SCANCODE_W);
							else if(event.jaxis.value > JOYSTICK_DEAD_ZONE)
								pressedKeys.insert(SDL_SCANCODE_S);
							if(event.jaxis.value >= -JOYSTICK_DEAD_ZONE && event.jaxis.value <= 0)
								pressedKeys.erase(SDL_SCANCODE_W);
							if(event.jaxis.value <= JOYSTICK_DEAD_ZONE && event.jaxis.value >= 0)
								pressedKeys.erase(SDL_SCANCODE_S);
						}
					} else if(event.jaxis.which == 1){
						fprintf(stderr, "Moving right stick\n");
					}
					break;
				case SDL_CONTROLLERBUTTONDOWN:
					// printf("Button pressed is %d\n", event.cbutton.button);
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
						case SDL_CONTROLLER_BUTTON_BACK:
							pressedKeys.insert(SDL_SCANCODE_M);
							break;
						case SDL_CONTROLLER_BUTTON_A:
							pressedKeys.insert(SDL_SCANCODE_DOWN);
							break;
						case SDL_CONTROLLER_BUTTON_B:
							pressedKeys.insert(SDL_SCANCODE_RIGHT);
							break;
						case SDL_CONTROLLER_BUTTON_X:
							pressedKeys.insert(SDL_SCANCODE_LEFT);
							break;
						case SDL_CONTROLLER_BUTTON_Y:
							pressedKeys.insert(SDL_SCANCODE_UP);
							break;
						case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
							pressedKeys.insert(SDL_SCANCODE_I);
							break;
						case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
							pressedKeys.insert(SDL_SCANCODE_Q);
							break;
						case SDL_CONTROLLER_BUTTON_START:
							paused = true;
							ps = new DisplayObject("pausescreen","resources/art/GamePaused.png");
							//myGame->loadTexture("resources/art/TitleScreen.png");
							AffineTransform at;
							ps->draw(at);
							SDL_RenderPresent(Game::renderer);

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
						case SDL_CONTROLLER_BUTTON_BACK:
							pressedKeys.erase(SDL_SCANCODE_M);
							break;
						case SDL_CONTROLLER_BUTTON_A:
							pressedKeys.erase(SDL_SCANCODE_DOWN);
							break;
						case SDL_CONTROLLER_BUTTON_B:
							pressedKeys.erase(SDL_SCANCODE_RIGHT);
							break;
						case SDL_CONTROLLER_BUTTON_X:
							pressedKeys.erase(SDL_SCANCODE_LEFT);
							break;
						case SDL_CONTROLLER_BUTTON_Y:
							pressedKeys.erase(SDL_SCANCODE_UP);
							break;
						case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
							pressedKeys.erase(SDL_SCANCODE_I);
							break;
						case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
							pressedKeys.erase(SDL_SCANCODE_Q);
							break;
						case SDL_CONTROLLER_BUTTON_START:
							pressedKeys.erase(SDL_SCANCODE_P);
							break;
					}
					break;
			}

		}else if(mapMode){
			SDL_Point offset = {0,0};
			speed = 1;
			while(mapMode){
				SDL_PollEvent(&event);
				if(event.type == SDL_CONTROLLERBUTTONUP){
					if(event.cbutton.button == SDL_CONTROLLER_BUTTON_BACK){
						mapMode = false;
						paused = false;
					}
				}
				if(event.type == SDL_KEYUP){
					if(event.key.keysym.scancode == SDL_SCANCODE_M){
						mapMode = false;
						paused = false;
					}
				}if(event.type == SDL_KEYDOWN){
					if(event.key.keysym.scancode == SDL_SCANCODE_UP){
						translateUp();
						offset.y -= 1;
						AffineTransform at;
						draw(at);
					}if(event.key.keysym.scancode == SDL_SCANCODE_DOWN){
						translateDown();
						offset.y += 1;
						AffineTransform at;
						draw(at);
					}if(event.key.keysym.scancode == SDL_SCANCODE_LEFT){
						translateLeft();
						offset.x -= 1;
						AffineTransform at;
						draw(at);
					}if(event.key.keysym.scancode == SDL_SCANCODE_RIGHT){
						translateRight();
						offset.x += 1;
						AffineTransform at;
						draw(at);
					}
				}

				if(event.type == SDL_QUIT){
						quit = true;
				}
			}
			speed = 5;
			moveTo(position.x - offset.x,position.y - offset.y);
		}
		else{
			// Game is paused
			SDL_PollEvent(&event);
			if(event.type == SDL_KEYDOWN){
				if(event.key.keysym.scancode == SDL_SCANCODE_P){
					paused = false;
					delete ps;
					ps = NULL;
				}
			} else if(event.type == SDL_CONTROLLERBUTTONDOWN){
				if(event.cbutton.button == SDL_CONTROLLER_BUTTON_START){
					paused = false;
					delete ps;
					ps = NULL;
				}
			}
			if(event.type == SDL_QUIT){
				quit = true;
			}

		}			
	}

	while(won){
		ws = new DisplayObject("winscreen","resources/art/GamePaused.png");
		AffineTransform at;
		ws->draw(at);
		SDL_RenderPresent(Game::renderer);
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT){
			won = false;
		}
	}

	if(ps != NULL){delete ps;}
	if(ws != NULL){delete ws;}
	
}

void Game::update(set<SDL_Scancode> pressedKeys){
	frameCounter++;
}
void Game::draw(AffineTransform &at){
}
