#include "DevTool.h"

using namespace std;

DevTool::DevTool() : DevLoop(1280, 720){
	DisplayObject* character = new DisplayObject("character", "./resources/character/Idle_1.png",true);
	Scene* scene = new Scene();
	scene->setRenderer(DevLoop::renderer);
	scene->id = "Scene";

	resourceBar = new ResourceBar(1280, 720, draggable, this,this->infoBar, DevLoop::renderer);
	resourceBar->setMouseListener(mouse);
	gridSize = 50.0; //in pixels
	//infoBar = this->infoBar;
	this->addChild(scene);
	this->infoBar->initThisWindow((DisplayObjectContainer *) this);
	// camera->addScene(scene);
	// this->addChild(mouse);
	this->addChild(character);
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
	//cout << "snapping to: " << x << " " << y << endl;
	return {x,y};


}

void DevTool::update(set<SDL_Scancode> pressedKeys){
	DevLoop::update(pressedKeys);

	// cout << *pressedKeys.begin() << endl;
	mouse->update(pressedKeys);
	DisplayObjectContainer::update(pressedKeys);

	if(infoBar->isEditing()){disable_input = true;}
	else					 disable_input = false;

	if(!disable_input) {
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
				case SDL_SCANCODE_H:
				{
					//cout << "Do stuff" << menu->vis<< endl;
					resourceBar->toggleVisibility();
					SDL_Delay(150);
					break;
				}
				case SDL_SCANCODE_P:
				{
					//  changeParent
					makeParent = true;
					break;
				}case SDL_SCANCODE_O:
				{
					//  changeParent
					makeParent = false;
					cout << makeParent << endl;
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
		draggable = leftClick(click_coords, ((DisplayObjectContainer *) this->getChild(SCENE_DOC_INDEX)));
	}
	else if(draggable != NULL){
		infoBar->updateObjectFields();
		draggable = NULL;
	}
	resourceBar->update(pressedKeys);
}

DisplayObject* DevTool::leftClick(SDL_Point click_coords, DisplayObjectContainer * c){
	for(DisplayObject* child : c->children){
		auto child_coords = child->getWorld();
		if (dist(child_coords, click_coords) < 30){
			cout << "Main checking " << child->id << " " << dist(child_coords, click_coords) <<  endl;
			if(makeParent){
				draggable = infoBar->curObj;
				if((dynamic_cast<DisplayObjectContainer*> (child)) == nullptr){
					continue;
				}
				if(infoBar->curObj != child){

					((DisplayObjectContainer*) infoBar->curObj->parent)->removeImmediateChildNoDelete(infoBar->curObj);
					infoBar->curObj->parent = child;
					makeParent = false;
					((DisplayObjectContainer*) child)->addChild(infoBar->curObj);

				}
			}else{
				draggable = child;
				infoBar->setObj(draggable);
			}
			infoBar->updateObjectFields();
			return draggable;
		}
		if((dynamic_cast<DisplayObjectContainer*> (child)) != nullptr){
			DisplayObject* ret = leftClick(click_coords,(DisplayObjectContainer *) child);
			if(ret != NULL){
				return ret;
			}
		}

	}return NULL;
}

void DevTool::draw(AffineTransform &at){
	DevLoop::draw(at);
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
