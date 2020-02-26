#include "Scene.h"
#include <iostream>
//#include "json.hpp"
//#include "jsonConversions.h"
// for convenience

Scene::Scene() :
		DisplayObjectContainer() {
	//just calling parent constructor
}

/* Load scene from a file */
void Scene::loadScene(string sceneFilePath) {
	//code retrieved from https://github.com/nlohmann/json
	std::ifstream i(sceneFilePath);
	//json j;
	int numObjects;
	int numDependencies;
	i >> numObjects;
	i >> numDependencies;
	
	vector<DisplayObject*> objects;
	objects.clear();

	while (numObjects--) {

		int type;
		i >> type;
		switch (type) {

		case 0: { //Scene
			Scene *temp = this;
			i >> id >> imgPath >> red >> green >> blue >> std::boolalpha >> vis >> std::boolalpha >> isRGB >> w >> h;
			objects.push_back(temp);
			if (temp->isRGB) {
				temp->loadRGBTexture(red, green, blue);
			} else if (temp->imgPath != "0") {
				temp->loadTexture(temp->imgPath);
			}
			break;
		}
		case 1: { //DisplayObject
			DisplayObject *temp = new DisplayObject();
			i >> temp->id >> temp->imgPath >> temp->red >> temp->green >> temp->blue >> std::boolalpha >> temp->vis >> std::boolalpha >> temp->isRGB >> temp->w >> temp->h;
			objects.push_back(temp);
			if (temp->isRGB) {
				temp->loadRGBTexture(red, green, blue);
			} else if (temp->imgPath != "") {
				temp->loadTexture(temp->imgPath);
			}
			break;
		}
		case 2: { //DisplayObjectContainer
			DisplayObjectContainer *temp = new DisplayObjectContainer();
			i >> temp->id >> temp->imgPath >> temp->red >> temp->green >> temp->blue >> std::boolalpha >> temp->vis >> std::boolalpha >> temp->isRGB >> temp->w >> temp->h;
			objects.push_back(temp);
			if (temp->isRGB) {
				temp->loadRGBTexture(red, green, blue);
			} else if (temp->imgPath != "") {
				temp->loadTexture(temp->imgPath);
			}
			break;
		}
		case 3: { //Sprite
			Sprite *temp = new Sprite();
			i >> temp->id >> temp->imgPath >> temp->red >> temp->green >> temp->blue >> std::boolalpha >> temp->vis >> std::boolalpha >> temp->isRGB >> temp->w >> temp->h;
			objects.push_back(temp);
			if (temp->isRGB) {
				temp->loadRGBTexture(red, green, blue);
			} else if (temp->imgPath != "") {
				temp->loadTexture(temp->imgPath);
			}
			break;
		}
		case 4: { //AnimatedSprite (haven't added some fields yet - needs to be finished). 
			Sprite *temp = new Sprite();
			i >> temp->id >> temp->imgPath >> temp->red >> temp->green >> temp->blue >> std::boolalpha >> temp->vis >> std::boolalpha >> temp->isRGB >> temp->w >> temp->h;
			objects.push_back(temp);
			break;
		}
		default: {
			cerr << "ERROR: Object type not recognized!\n";
			break;
		}

		}
		//this = j.get<Scene::Scene>();
		//return s;
	}
	while (numDependencies--) {
		string id1, id2;
		i >> id1 >> id2;
		DisplayObjectContainer *temp1;
		DisplayObject *temp2;

		for (vector<DisplayObject*>::iterator it = objects.begin(); it != objects.end(); it++) {
			if (id1 == (*it)->id) {
				temp1 = (DisplayObjectContainer*) (*it);
			}
		}

		for (vector<DisplayObject*>::iterator it = objects.begin(); it != objects.end(); it++) {
			if (id2 == (*it)->id) {
				temp2 = *it;
			}
		}
		temp1->addChild(temp2);
	}

}

void Scene::saveScene(string sceneFilePath) {
	//code retrieved from https://github.com/nlohmann/json
//	json j = this;
//	std::ofstream o(sceneFilePath);
//	o << std::setw(4) << j << std::endl;
}

void Scene::update(set<SDL_Scancode> pressedKeys) {
	DisplayObjectContainer::update(pressedKeys);
}
void Scene::draw(AffineTransform &at) {
	DisplayObjectContainer::draw(at);
}
