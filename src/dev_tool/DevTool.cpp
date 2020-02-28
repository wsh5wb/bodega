#include "DevTool.h"

using namespace std;

DevTool::DevTool() : Game(1280, 720){
	camera = Camera::getCamera();
	Scene* scene = new Scene();
	scene->id = "Scene";
	this->infoBar->initThisWindow(this);
	resourceBar = new ResourceBar(1280, 720, draggable, this,this->infoBar);
	resourceBar->setMouseListener(mouse);
	//infoBar = this->infoBar;
	this->addChild(scene);
	// camera->addScene(scene);
	this->addChild(mouse);
}

DevTool::~DevTool(){
	delete resourceBar;
}


void DevTool::update(set<SDL_Scancode> pressedKeys){
	Game::update(pressedKeys);
	if(!disable_camera) DisplayObjectContainer::update(pressedKeys);

	if (draggable != NULL and mouse->leftClick){
		auto point = mouse->getCoordinates();
		draggable->moveTo(point.x, point.y);
	}
	else if(mouse->leftClick){
		auto click_coords = mouse->getCoordinates();
		for(DisplayObject* child : this->children){
			auto child_coords = child->getWorld();
			if (dist(child_coords, click_coords) < 30){
				cout << "Main checking " << child->id << " " << dist(child_coords, click_coords) <<  endl;
				draggable = child;
				break;
			}
		}
	}
	else if(draggable != NULL){
		draggable = NULL;
	}
	resourceBar->update(pressedKeys);
}


void DevTool::draw(AffineTransform &at){
	Game::draw(at);
	camera->draw(at);
	DisplayObjectContainer::draw(at);
	resourceBar->draw(at);
}


int main(int argc, char ** argv){
	DevTool* devTool = new DevTool();
 	devTool->start();
 	delete devTool;
	return 0;
}
