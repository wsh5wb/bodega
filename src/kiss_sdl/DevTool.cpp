#include "DevTool.h"

using namespace std;

DevTool::DevTool() : Game(1200, 1000){
	child = new DisplayObjectContainer("girl", "./resources/character/Idle_1.png");
	Scene* scene = new Scene();
	scene->loadScene("./resources/scenes/test.txt");
	this->addChild(mouse);
	// this->addChild(child);
	this->addChild(scene);
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

	DisplayObjectContainer::draw(at);


}


int main(int argc, char ** argv){
	DevTool* devTool = new DevTool();
 	devTool->start();
 	delete devTool;
	return 0;
}
