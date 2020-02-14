#include "Scene.h"
//#include "json.hpp"
//#include "jsonConversions.h"
// for convenience

Scene(): DisplayObjectContainer() {
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

//	j.at("id").get_to(p.id);
//		j.at("imgPath").get_to(p.imgPath);
//		j.at("red").get_to(p.red);
//		j.at("green").get_to(p.green);
//		j.at("blue").get_to(p.blue);
//		j.at("type").get_to(p.type);
//		j.at("vis").get_to(p.vis);
//		j.at("isRGB").get_to(p.isRGB);
//		j.at("w").get_to(p.w);
//		j.at("h").get_to(p.h);
//		j.at("children").get_to(p.children);
	vector<DisplayObject*> objects;
	while (numObjects--) {
		string type;
		i >> type;
		switch (type) {

		case "Scene": {
			Scene temp = new Scene();
			i >> temp->id >> temp->imgPath >> temp->red >> temp->green >> temp->blue >> std::boolalpha >> temp->vis >> std::boolalpha >> temp->isRGB >> temp->w >> temp->h;
			objects.push_back(temp);
			break;
		}
		case "DisplayObject": {
			Scene temp = new DisplayObject();
			i >> temp->id >> temp->imgPath >> temp->red >> temp->green >> temp->blue >> std::boolalpha >> temp->vis >> std::boolalpha >> temp->isRGB >> temp->w >> temp->h;
			objects.push_back(temp);
			break;
		}
		case "DisplayObjectContainer": {
			Scene temp = new DisplayObjectContainer();
			i >> temp->id >> temp->imgPath >> temp->red >> temp->green >> temp->blue >> std::boolalpha >> temp->vis >> std::boolalpha >> temp->isRGB >> temp->w >> temp->h;
			objects.push_back(temp);
			break;
		}
		case "Sprite": {
			Scene temp = new Sprite();
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
				temp1 = it;
			}
		}

		for (vector<DisplayObject*>::iterator it = objects.begin(); it != objects.end(); it++) {
			if (id2 == (*it)->id) {
				temp2 = it;
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
