#include "DisplayObjectContainer.h"
#include "DTEvent.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include "Player.h"

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

		if((*it) != Player::getPlayer()){
			DTEvent e("OBJ_RM", &Game::eventHandler, *it);
			Game::eventHandler.dispatchEvent(&e);
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

	for (DisplayObject *c: children) {
		if(child == c){
			DTEvent e("OBJ_RM", &Game::eventHandler, child);
			Game::eventHandler.dispatchEvent(&e);
			/*delete c;
			c = NULL;
			child = NULL;*/
			c->shouldDelete = true;
			c->shouldRemove = true;
			return;
		}
	}
	/*for (vector<DisplayObject*>::iterator it = children.begin();
			it != children.end(); ++it) {
		if (child == *it) {
			DTEvent e("OBJ_RM", &Game::eventHandler, child);
			Game::eventHandler.dispatchEvent(&e);
			//cout << "deleted " << (*it)->id << *it << endl;
			//delete *it;
			*it = NULL;
			//children.erase(it);
			return;
		}
	}*/
}

void DisplayObjectContainer::removeImmediateChild(string id) {

	for (DisplayObject *c: children) {
		if(c->id == id){
			DTEvent e("OBJ_RM", &Game::eventHandler, c);
			Game::eventHandler.dispatchEvent(&e);
			c = NULL;
			c->shouldRemove = true;
			return;
		}
	}
	/*for (vector<DisplayObject*>::iterator it = children.begin();
			it != children.end(); it++) {
		if (id == (*it)->id) {
			DTEvent e("OBJ_RM", &Game::eventHandler, *it);
			Game::eventHandler.dispatchEvent(&e);
			//delete *it;
			*it = NULL;
			//children.erase(it);
			break;
		}
	}*/
}

void DisplayObjectContainer::removeImmediateChildNow(DisplayObject* child){
	for (vector<DisplayObject*>::iterator it = children.begin();it != children.end(); ++it) {
		if (child == *it) {
			DTEvent e("OBJ_RM", &Game::eventHandler, child);
			Game::eventHandler.dispatchEvent(&e);
			//cout << "deleted " << (*it)->id << *it << endl;
			delete *it;
			*it = NULL;
			child = NULL;
			children.erase(it);
			return;
		}
	}
}

void DisplayObjectContainer::removeImmediateChildNoDelete(DisplayObject* child){
	for(vector<DisplayObject*>::iterator it = children.begin(); it != children.end(); it++){
		if(child == *it){
			DTEvent e("OBJ_RM", &Game::eventHandler, *it);
			Game::eventHandler.dispatchEvent(&e);
			children.erase(it);
			*it = NULL;
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
	int sz = children.size();
	for(int i = 0;i<sz;i++){
		if(children[i] == NULL){continue;}
		children[i]->resetDelta();
	}
	/*for (DisplayObject *child : children) {
		//cout << "child " << child->id << endl;
		if(child != NULL)
			child->resetDelta();
	}*/
}

void DisplayObjectContainer::update(set<SDL_Scancode> pressedKeys) {
	DisplayObject::update(pressedKeys);
	//int i = 0;
	int sz = children.size();
	
	/*for (DisplayObject *child : children) {
		i++;
		cout << "i " << i << " " << id << endl;
		if(child == NULL){continue;}
		child->update(pressedKeys);
	}*/for(int i = 0;i<sz;i++){
		if(children[i] == NULL){
			continue;}
		children[i]->update(pressedKeys);
	}
	/*for(vector<DisplayObject*>::iterator it = children.begin();it != children.end(); ++it){
		if(*it == NULL){continue;}
		(*it)->update(pressedKeys);
	}*/

	for(vector<DisplayObject*>::iterator it = children.begin();it != children.end();){
		if((*it)->shouldRemove){
			//delete *it;
			if((*it)->shouldDelete) {delete *it;}
			it = children.erase(it);
		}else{
			it++;
		}
		//(*it)->update(pressedKeys);
	}
	/*for (DisplayObject *child : children) {
		i++;
		cout << "i " << i << " " << id << endl;
		if(child == NULL){continue;}
		child->update(pressedKeys);
	}*/
}

void DisplayObjectContainer::draw(AffineTransform &at) {
	for(vector<DisplayObject*>::iterator it = children.begin();it != children.end();){
		if(*it == NULL){
			//delete *it;
			it = children.erase(it);
		}else{
			it++;
		}
		//(*it)->update(pressedKeys);
	}
	DisplayObject::draw(at);
	DisplayObject::applyTransformations(at);
	int sz = children.size();
	for(int i =0; i < sz; i++){
		if(children[i] == NULL){continue;}
		children[i]->draw(at);
	}
	/*for (DisplayObject *child : children) {
		/*if((dynamic_cast<DisplayObjectContainer*>(child)) != nullptr){

		 }
		 if(child == NULL){continue;}
		child->draw(at);
	}*/

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

void DisplayObjectContainer::cleanUpDisplayTree() {
	for (auto child : children) {
		if (child) {
			child->cleanUpDisplayTree();
			child->parent = NULL;
			if (child != Player::getPlayer()) {
				free(child);
			}
		}
	}
	children.clear();
}
