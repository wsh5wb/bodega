#include "DisplayObjectContainer.h"
#include <iostream>

using namespace std;

DisplayObjectContainer::DisplayObjectContainer() : DisplayObject(){
	
}

DisplayObjectContainer::DisplayObjectContainer(string id, string filepath) : DisplayObject(id,filepath,false){
	
}

DisplayObjectContainer::DisplayObjectContainer(string id, string filepath, SDL_Renderer* renderer) : 
	DisplayObject(id,filepath,renderer,false){
	
}

DisplayObjectContainer::DisplayObjectContainer(string id, int red, int green, int blue, SDL_Renderer* renderer) :
	DisplayObject(id,red,green,blue,renderer){

}

DisplayObjectContainer::DisplayObjectContainer(string id, int red, int green, int blue) : DisplayObject(id,red,green,blue){

}

DisplayObjectContainer::~DisplayObjectContainer(){
	for(vector<DisplayObject*>::iterator it = children.begin(); it != children.end(); it++){
		delete *it;
	}children.clear();
}

void DisplayObjectContainer::addChild(DisplayObject* child){
	children.push_back(child);
	child->parent = this;
}

void DisplayObjectContainer::removeImmediateChild(DisplayObject* child){
	for(vector<DisplayObject*>::iterator it = children.begin(); it != children.end(); it++){
		if(child == *it){
			delete *it;
			children.erase(it);
			break;
		}
	}
}

void DisplayObjectContainer::removeImmediateChild(string id){
	for(vector<DisplayObject*>::iterator it = children.begin(); it != children.end(); it++){
		if(id == (*it)->id){
			delete *it;
			children.erase(it);
			break;
		}
	}
}


void DisplayObjectContainer::removeImmediateChildNoDelete(DisplayObject* child){
	for(vector<DisplayObject*>::iterator it = children.begin(); it != children.end(); it++){
		if(child == *it){
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
	}
	return NULL;
}

void DisplayObjectContainer::update(set<SDL_Scancode> pressedKeys){
	DisplayObject::update(pressedKeys);

	for(DisplayObject* child : children){
		child->update(pressedKeys);
	}
}

void DisplayObjectContainer::draw(AffineTransform &at){
	if(this == NULL){
		cout << "NULL";
		return;
	}
	DisplayObject::draw(at);
	DisplayObject::applyTransformations(at);

	for(DisplayObject* child : children){
		if(child != NULL){
			child->draw(at);

		}
		
	}
	
	DisplayObject::reverseTransformations(at);	
}

void DisplayObjectContainer::saveSelf(vector<string> &objects,
		vector<string> &dependencies) {
	string desc;
	stringstream sstm;
	int px0 = pivot.x, px1 = position.x, py0 = pivot.y, py1 = position.y;
	sstm << "1 " << id << " " << imgPath << " " << red << " " << green << " "
			<< blue << " " << std::boolalpha << vis << " " << std::boolalpha
			<< isRGB << " " << w << " " << h << " " << speed << " " << scaleX
			<< " " << scaleY << " " << rotation << " " << rotationAmount << " "
			<< alpha << " " << px0 << " " << py0 << " " << px1 << " " << py1
			<< "\n";
	desc = sstm.str();
	objects.push_back(desc);
}