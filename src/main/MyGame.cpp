#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "Scene.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "MyGame.h"
#include "TweenJuggler.h"

using namespace std;
/*	this->alpha = 0;
	printf("1");
	TweenJuggler * juggle = TweenJuggler::getInstance();
	printf("1");
	Tween * alpha_tween = new Tween(this);
	printf("1");
	alpha_tween->animate(TWEEN_ALPHA, this->alpha, 255, 100, TWEEN_LINEAR, EASE_IN);
	printf("1");
	juggle->add(alpha_tween);*/


MyGame::MyGame() : Game(1200, 900) {
	Game::eventHandler.addEventListener((EventListener*) &Game::cs, "OBJ_ADD");
	Game::eventHandler.addEventListener((EventListener*) &Game::cs, "OBJ_RM");

	myCamera = Camera::getCamera();
	dungeon = new HadesDungeon();
	dungeon->generate();
	myCamera->addScene(dungeon);

	effect.loadMusic("./resources/sounds/clock_ticking.wav");

	animationJuggler = TweenJuggler::getInstance();

//	enemy = new Enemy((Player*) character->getChild("PLAYER_YOU"));
//
//	this->addChild(character);
//	this->addChild(enemy);
//
//	Game::cs.watchForCollisions("ENEMY", "PLAYER");
	Game::cs.watchForCollisions("PLAYER", "DOOR");
	// Come up with more elegant solution to determining which dir to go.
	Game::eventHandler.addEventListener((EventListener*) dungeon, "DUNG_TRANS_U");
	Game::eventHandler.addEventListener((EventListener*) dungeon, "DUNG_TRANS_D");
	Game::eventHandler.addEventListener((EventListener*) dungeon, "DUNG_TRANS_R");
	Game::eventHandler.addEventListener((EventListener*) dungeon, "DUNG_TRANS_L");


}

MyGame::~MyGame() {
	Scene* character = new Scene();
	character->addChild(myCamera->container);
	//character->saveScene("./resources/scenes/testSave3.txt");
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
//	if (x >= xminZ && x <= xmaxZ && y > yminZ && y <= ymaxZ) {
//		myCamera->setZoom(500, 500);
//	} else {
//		myCamera->setZoom(500, 500);
//	}

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
//		case SDL_SCANCODE_Q: {
//			//character->scaleOut();
//			myCamera->zoom(2, 2);
//			break;
//		}
//		case SDL_SCANCODE_W: {
//			//character->scaleIn();
//			myCamera->zoom(1.0/GRID_SIZE, 1.0/GRID_SIZE);
//			break;
//		}
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

	Game::cs.update();

}

void MyGame::draw(AffineTransform &at) {
	Game::draw(at);
//	myCamera->draw(at);
	SDL_RenderClear(Game::renderer);
	myCamera->draw(at);
	DisplayObjectContainer::draw(at);
	animationJuggler->nextFrame();
	SDL_RenderPresent(Game::renderer);
}
