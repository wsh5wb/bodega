#include "DevTool.h"

using namespace std;

DevTool::DevTool() : Game(1280, 720){
	child = new DisplayObjectContainer("girl", "./resources/character/Idle_1.png");
	Scene* scene = new Scene();
	scene->loadScene("./resources/scenes/test.txt");
	resourceBar = new ResourceBar(1280, 720, draggable);
	resourceBar->setMouseListener(mouse);
	//this->addChild(resourceBar);
	this->addChild(scene);
	this->addChild(mouse);
}

DevTool::~DevTool(){
	//delete resourceBar;
}


void DevTool::update(set<SDL_Scancode> pressedKeys){
	Game::update(pressedKeys);
	DisplayObjectContainer::update(pressedKeys);
	resourceBar->update(pressedKeys);

}


void DevTool::draw(AffineTransform &at){
	Game::draw(at);
	DisplayObjectContainer::draw(at);
	resourceBar->draw(at);
}


int main(int argc, char ** argv){
	DevTool* devTool = new DevTool();
 	devTool->start();
 	delete devTool;
	return 0;
}
