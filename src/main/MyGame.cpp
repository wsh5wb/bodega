#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "Scene.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "MyGame.h"

using namespace std;


MyGame::MyGame() : Game(1200, 900) {
	myCamera = Camera::getCamera();
	dungeon = new HadesDungeon();
	dungeon->generate();
	myCamera->addScene(dungeon);

	effect.loadMusic("./resources/sounds/clock_ticking.wav");

//	enemy = new Enemy((Player*) character->getChild("PLAYER_YOU"));
//
//	this->addChild(character);
//	this->addChild(enemy);
//
//	Game::cs.watchForCollisions("ENEMY", "PLAYER");

}

MyGame::~MyGame() {
//	character->saveScene("./resources/scenes/testSave2.txt");
//	std::ofstream o("./resources/scenes/test.txt");
//	o << "2 1" << std::endl;
//	o << "0 " << "Scene" << " "<< "0" << " " << "0" << " "<< "0" << " "<< "0" << " "<< "true" << " "<< "false"  << " "<< "0" << " "<< "0" << std::endl;
//	o << "3 " << character->id << " "<< character->imgPath << " " << character->red << " "<< character->green << " "<< character->blue << " "<< std::boolalpha << character->vis << " "<< std::boolalpha << character->isRGB << " "<< character->w << " "<< character->h << std::endl;
//	o << "Scene" << " " << character->id << std::endl;
	//cerr << character->numChildren();
}

void MyGame::update(set<SDL_Scancode> pressedKeys) {

	Game::update(pressedKeys);
	DisplayObjectContainer::update(pressedKeys);
	myCamera->update(pressedKeys);

	int x = myCamera->x;
	int y = myCamera->y;

	int cs = 0;

	//these need to be set
	int xmin = 0;
	int ymin = 0;
	int xmax = 0;
	int ymax = 0;

	int xmax2 = 0;
	int ymin2 = 0;

	//these need to be set
	int xminZ = 0;
	int yminZ = 0;
	int xmaxZ = 0;
	int ymaxZ = 0;

	//bounds can also be done like this
	if (x >= xminZ && x <= xmaxZ && y > yminZ && y <= ymaxZ) {
		myCamera->setZoom(500, 500);
	} else {
		myCamera->setZoom(500, 500);
	}

	for (SDL_Scancode code : pressedKeys) {
		switch (code) {

		case SDL_SCANCODE_DOWN: {
			//character->translateDown();
			if (y < ymax)
				myCamera->pan(0, cs);
			break;
		}
		case SDL_SCANCODE_UP: {
			//character->translateUp();
			if ((y >= ymin && x <= xmax2) || y >= ymin2)
				myCamera->pan(0, -cs);
			break;
		}
		case SDL_SCANCODE_LEFT: {
			//character->translateLeft();
			if (x > xmin)
				myCamera->pan(-cs, 0);
			break;
		}
		case SDL_SCANCODE_RIGHT: {
			//character->translateRight();
			if ((x < xmax && y > ymin2) || x < xmax2)
				myCamera->pan(cs, 0);
			break;
		}
		case SDL_SCANCODE_Q: {
			//character->scaleOut();
			myCamera->zoom(2, 2);
			break;
		}
		case SDL_SCANCODE_W: {
			//character->scaleIn();
			myCamera->zoom(.2, .2);
			break;
		}
			//case SDL_SCANCODE_A:
			// {
			// 	character->rotateCW();
			// 	break;
			// }case SDL_SCANCODE_S:
			// {
			// 	character->rotateCCW();
			// 	break;
			// }
			// case SDL_SCANCODE_I: 
			// {
			// 	character->movePivotUp();
			// 	break;
			// }case SDL_SCANCODE_J:
			// {
			// 	character->movePivotLeft();
			// 	break;
			// }case SDL_SCANCODE_K:
			// {
			// 	character->movePivotDown();
			// 	break;
			// }case SDL_SCANCODE_L:
			// {
			// 	character->movePivotRight();
			// 	break;

			// }case SDL_SCANCODE_Z:
			// {
			// 	character->increaseAlpha();
			// 	break;
			// }case SDL_SCANCODE_X:
			// {
			// 	character->decreaseAlpha();
			// 	break;
			// }

		case SDL_SCANCODE_P: {
			effect.playMusic();
			break;
		}
		}
	}


}

void MyGame::draw(AffineTransform &at) {
	Game::draw(at);
//	myCamera->draw(at);
	SDL_RenderClear(Game::renderer);
	myCamera->draw(at);
	DisplayObjectContainer::draw(at);
	SDL_RenderPresent(Game::renderer);
}
