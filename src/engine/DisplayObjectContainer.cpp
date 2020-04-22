#include "DisplayObjectContainer.h"
#include "DTEvent.h"
#include "Game.h"
#include "Player.h"
#include <iostream>

using namespace std;

DisplayObjectContainer::DisplayObjectContainer() :
		DisplayObject() {
}

DisplayObjectContainer::DisplayObjectContainer(string id, string filepath) :
		DisplayObject(id, filepath) {

}

DisplayObjectContainer::DisplayObjectContainer(string id, string filepath,
		bool particle) :
		DisplayObject(id, filepath, particle) {
	if (particle) {
		return;
	}
}

DisplayObjectContainer::DisplayObjectContainer(string id, int red, int green,
		int blue) :
		DisplayObject(id, red, green, blue) {

}

DisplayObjectContainer::~DisplayObjectContainer() {
	for (vector<DisplayObject*>::iterator it = children.begin();
			it != children.end(); it++) {
		// probably change to check if in collision system first, then signal.
		// this allows to change rm case of cs.handleEvent();
		DTEvent e("OBJ_RM", &Game::eventHandler, *it);
		Game::eventHandler.dispatchEvent(&e);

		if((*it) != Player::getPlayer()){
			delete *it;
			*it = NULL;
		}

	}
	children.clear();
}

void DisplayObjectContainer::addChild(DisplayObject *child) {
	children.push_back(child);
	child->parent = this;
	DTEvent e("OBJ_ADD", &Game::eventHandler, child);
	Game::eventHandler.dispatchEvent(&e);
}

void DisplayObjectContainer::addToCollisionSystem(){
	DTEvent e("OBJ_ADD", &Game::eventHandler, this);
	Game::eventHandler.dispatchEvent(&e);
	for(DisplayObject* child : children){
		if(dynamic_cast<DisplayObjectContainer*>(child) == nullptr){
			DTEvent e("OBJ_ADD", &Game::eventHandler, child);
			Game::eventHandler.dispatchEvent(&e);
		} else	((DisplayObjectContainer*) child)->addToCollisionSystem();
	}
}

void DisplayObjectContainer::removeFromCollisionSystem(){
	DTEvent e("OBJ_RM", &Game::eventHandler, this);
	Game::eventHandler.dispatchEvent(&e);
	for(DisplayObject* child : children){
		if(dynamic_cast<DisplayObjectContainer*>(child) == nullptr){
			DTEvent e("OBJ_RM", &Game::eventHandler, child);
			Game::eventHandler.dispatchEvent(&e);
		} else	((DisplayObjectContainer*) child)->addToCollisionSystem();
	}
}


void DisplayObjectContainer::removeImmediateChild(DisplayObject *child) {
	for (vector<DisplayObject*>::iterator it = children.begin();
			it != children.end(); it++) {
		if (child == *it) {
			DTEvent e("OBJ_RM", &Game::eventHandler, child);
			Game::eventHandler.dispatchEvent(&e);
			delete *it;
			*it = NULL;
			children.erase(it);
			break;
		}
	}
}

void DisplayObjectContainer::removeImmediateChild(string id) {
	for (vector<DisplayObject*>::iterator it = children.begin();
			it != children.end(); it++) {
		if (id == (*it)->id) {
			DTEvent e("OBJ_RM", &Game::eventHandler, *it);
			Game::eventHandler.dispatchEvent(&e);
			delete *it;
			*it = NULL;
			children.erase(it);
			break;
		}
	}
}

void DisplayObjectContainer::removeImmediateChildNoDelete(DisplayObject* child){
	for(vector<DisplayObject*>::iterator it = children.begin(); it != children.end(); it++){
		if(child == *it){
			DTEvent e("OBJ_RM", &Game::eventHandler, *it);
			Game::eventHandler.dispatchEvent(&e);
			children.erase(it);
			break;
		}
	}
}

void DisplayObjectContainer::removeChild(int index) {
	vector<DisplayObject*>::iterator it = children.begin() + index;
	DTEvent e("OBJ_RM", &Game::eventHandler, *it);
	Game::eventHandler.dispatchEvent(&e);
	delete *it;
	*it = NULL;
	children.erase(it);
}

void DisplayObjectContainer::removeThis() {
	for (vector<DisplayObject*>::iterator it = children.begin();
			it != children.end(); it++) {
		DTEvent e("OBJ_RM", &Game::eventHandler, *it);
		Game::eventHandler.dispatchEvent(&e);
		delete *it;
		*it = NULL;
	}
	children.clear();
}

int DisplayObjectContainer::numChildren() {
	return children.size();
}

DisplayObject* DisplayObjectContainer::getChild(int index) {
	return children[index];
}

DisplayObject* DisplayObjectContainer::getChild(string id) {
	for (vector<DisplayObject*>::iterator it = children.begin();
			it != children.end(); it++) {
		if (id == (*it)->id) {
			return *it;
		}
	}
	return NULL;
}

void DisplayObjectContainer::resetDelta() {
	DisplayObject::resetDelta();
	for (DisplayObject *child : children) {
		//cout << "child " << child->id << endl;
		child->resetDelta();
	}
}

void DisplayObjectContainer::update(set<SDL_Scancode> pressedKeys) {
	DisplayObject::update(pressedKeys);
	for (DisplayObject *child : children) {
		child->update(pressedKeys);
	}
}

void DisplayObjectContainer::draw(AffineTransform &at) {
	DisplayObject::draw(at);
	DisplayObject::applyTransformations(at);

	for (DisplayObject *child : children) {
		/*if((dynamic_cast<DisplayObjectContainer*>(child)) != nullptr){

		 }
		 */
		child->draw(at);
	}

	DisplayObject::reverseTransformations(at);
}

void DisplayObjectContainer::saveSelf(vector<string> &objects,
		vector<string> &dependencies) {
	string desc;
	stringstream sstm;
	int px0 = pivot.x, px1 = position.x, py0 = pivot.y, py1 = position.y;
	sstm << "2 " << id << " " << imgPath << " " << red << " " << green << " "
			<< blue << " " << std::boolalpha << vis << " " << std::boolalpha
			<< isRGB << " " << w << " " << h << " " << speed << " " << scaleX
			<< " " << scaleY << " " << rotation << " " << rotationAmount << " "
			<< alpha << " " << px0 << " " << py0 << " " << px1 << " " << py1
			<< "\n";
	desc = sstm.str();
	objects.push_back(desc);
	for (DisplayObject *child : children) {
		string dep = id + " " + child->id + "\n";
		dependencies.push_back(dep);
		child->saveSelf(objects, dependencies);
	}
}
