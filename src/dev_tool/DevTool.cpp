#include "DevTool.h"

using namespace std;

DevTool::DevTool() : Game(1280, 720){
	Scene* scene = new Scene();

	scene->id = "Scene";

	resourceBar = new ResourceBar(1280, 720, draggable, this,this->infoBar);
	resourceBar->setMouseListener(mouse);
	gridSize = 50.0; //in pixels
	//infoBar = this->infoBar;
	this->addChild(scene);
	this->infoBar->initThisWindow((DisplayObjectContainer *) this->getChild(SCENE_DOC_INDEX));
	// camera->addScene(scene);
	//this->addChild(mouse);
}

DevTool::~DevTool(){
	delete resourceBar;
}

SDL_Point DevTool::snapToGrid(SDL_Point coords){
	int x = coords.x;
	int y = coords.y;

	if(x % (int) gridSize > gridSize / 2.){
		x = gridSize * (((int) (x/gridSize)) + 1);
	}
	else{
		x = gridSize * (int) (x/gridSize);
	}
	if(y % (int) gridSize > gridSize / 2.){
		y = gridSize * (((int) (y/gridSize)) + 1);
	}
	else{
		y = gridSize * (int) (y/gridSize);
	}
	cout << "snapping to: " << x << " " << y << endl;
	return {x,y};


}

void DevTool::update(set<SDL_Scancode> pressedKeys){
	Game::update(pressedKeys);

	mouse->update(pressedKeys);
	DisplayObjectContainer::update(pressedKeys);

	if(!disable_camera) {
		for(SDL_Scancode code : pressedKeys){
			switch(code){
				case SDL_SCANCODE_W:
				{
					children[SCENE_DOC_INDEX]->translateDown();
					break;
				}
				case SDL_SCANCODE_A:
				{
					children[SCENE_DOC_INDEX]->translateRight();
					break;
				}
				case SDL_SCANCODE_S:
				{
					children[SCENE_DOC_INDEX]->translateUp();
					break;
				}
				case SDL_SCANCODE_D:
				{
					children[SCENE_DOC_INDEX]->translateLeft();
					break;
				}
				case SDL_SCANCODE_Z:
				{
					children[SCENE_DOC_INDEX]->scale(1.05);
					break;
				}
				case SDL_SCANCODE_X:
				{
					children[SCENE_DOC_INDEX]->scale(.95);
					break;
				}
			}
		}
	}


	if (draggable != NULL and mouse->leftClick){
		infoBar->updateObjectFields();
		auto point = mouse->getCoordinates();
		point = snapToGrid(point);
		draggable->moveTo(point.x, point.y);
	}
	else if(mouse->leftClick){
		auto click_coords = mouse->getCoordinates();

		for(DisplayObject* child : ((DisplayObjectContainer *) this->getChild(SCENE_DOC_INDEX))->children){
			auto child_coords = child->getWorld();
			if (dist(child_coords, click_coords) < 30){
				cout << "Main checking " << child->id << " " << dist(child_coords, click_coords) <<  endl;
				draggable = child;
				infoBar->setObj(draggable);
				break;
			}
		}
	}
	else if(draggable != NULL){
		infoBar->updateObjectFields();
		// auto point = draggable->getWorld();
		// point = snapToGrid(point);
		// draggable->moveTo(point.x, point.y);

		draggable = NULL;
	}
	resourceBar->update(pressedKeys);
}

void DevTool::draw(AffineTransform &at){
	Game::draw(at);
	DisplayObjectContainer::draw(at);
	// mouse->draw(at);
	resourceBar->draw(at);
}


int main(int argc, char ** argv){
	DevTool* devTool = new DevTool();
 	devTool->start();
 	delete devTool;
	return 0;
}
