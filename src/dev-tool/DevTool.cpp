#include "DevTool.h"

using namespace std;

DevTool::DevTool() : Game(1200, 1000){
	resourceBar = new ResourceBar(this->windowWidth, this->windowHeight);
	resourceBar->setMouseListener(mouse);
	this->addChild(resourceBar);
	this->addChild(mouse);

}

DevTool::~DevTool(){
	// delete resourceBar;
}


void DevTool::update(set<SDL_Scancode> pressedKeys){
	Game::update(pressedKeys);
	DisplayObjectContainer::update(pressedKeys);
}


void DevTool::draw(AffineTransform &at){
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
	DisplayObjectContainer::draw(at);
	SDL_RenderPresent(Game::renderer);

}


int main(int argc, char ** argv){
	DevTool* devTool = new DevTool();
 	devTool->start();
 	delete devTool;
	return 0;
}