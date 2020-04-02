#include "DisplayObjectContainer.h"
#include "DTEvent.h"
#include "Game.h"
#include <iostream>

using namespace std;

DisplayObjectContainer::DisplayObjectContainer() : DisplayObject(){
	this->addEventListener((EventListener*) &Game::cs, "OBJ_ADD");
	this->addEventListener((EventListener*) &Game::cs, "OBJ_RM");
}

DisplayObjectContainer::DisplayObjectContainer(string id, string filepath, bool particle) : DisplayObject(id,filepath,particle){
	if(particle) {return;}
	this->addEventListener((EventListener*) &Game::cs, "OBJ_ADD");
	this->addEventListener((EventListener*) &Game::cs, "OBJ_RM");
}

DisplayObjectContainer::DisplayObjectContainer(string id, int red, int green, int blue) : DisplayObject(id,red,green,blue){
	this->addEventListener((EventListener*) &Game::cs, "OBJ_ADD");
	this->addEventListener((EventListener*) &Game::cs, "OBJ_RM");
}

DisplayObjectContainer::~DisplayObjectContainer(){
	for(vector<DisplayObject*>::iterator it = children.begin(); it != children.end(); it++){
		delete *it;
	}children.clear();
}

void DisplayObjectContainer::addChild(DisplayObject* child){
	children.push_back(child);
	child->parent = this;
	DTEvent e("OBJ_ADD", this, child);
	this->dispatchEvent(&e);
}

void DisplayObjectContainer::removeImmediateChild(DisplayObject* child){
	for(vector<DisplayObject*>::iterator it = children.begin(); it != children.end(); it++){
		if(child == *it){
			DTEvent e("OBJ_RM", this, child);
			this->dispatchEvent(&e);
			delete *it;
			children.erase(it);
			break;
		}
	}
}

void DisplayObjectContainer::removeImmediateChild(string id){
	for(vector<DisplayObject*>::iterator it = children.begin(); it != children.end(); it++){
		if(id == (*it)->id){
			DTEvent e("OBJ_RM", this, *it);
			this->dispatchEvent(&e);
			delete *it;
			children.erase(it);
			break;
		}
	}
}

void DisplayObjectContainer::removeChild(int index){
	vector<DisplayObject*>::iterator it = children.begin() + index;
	delete *it;
	children.erase(it);
}

void DisplayObjectContainer::removeThis(){
	for(vector<DisplayObject*>::iterator it = children.begin(); it != children.end(); it++){
		delete *it;
	}children.clear();
}

int DisplayObjectContainer::numChildren(){
	return children.size();
}

DisplayObject* DisplayObjectContainer::getChild(int index){
	return children[index];
}

DisplayObject* DisplayObjectContainer::getChild(string id){
	for(vector<DisplayObject*>::iterator it = children.begin(); it != children.end(); it++){
		if(id == (*it)->id){ return *it; }
	}return NULL;
}

void DisplayObjectContainer::update(set<SDL_Scancode> pressedKeys){
	DisplayObject::update(pressedKeys);
	for(DisplayObject* child : children){
		child->update(pressedKeys);
	}
}

void DisplayObjectContainer::draw(AffineTransform &at){
	DisplayObject::draw(at);
	DisplayObject::applyTransformations(at);

	for(DisplayObject* child : children){
		child->draw(at);
	}
	
	DisplayObject::reverseTransformations(at);	
}