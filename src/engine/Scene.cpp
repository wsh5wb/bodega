#include "Scene.h"
#include <iostream>
#include <sstream>

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
			int speed;
			double scaleX;
			double scaleY;
			double rotation;
			double rotationAmount;
			int alpha;
			SDL_Point pivot, position;
			i >> id >> imgPath >> red >> green >> blue >> std::boolalpha >> vis
					>> std::boolalpha >> isRGB >> w >> h >> speed >> scaleX
					>> scaleY >> rotation >> rotationAmount >> alpha >> pivot.x
					>> pivot.y >> position.x >> position.y;
			temp->setSpeed(speed);
			temp->setScale(scaleX, scaleY);
			temp->setRotationValue(rotation);
			temp->setRotation(rotationAmount);
			temp->setAlpha(alpha);
			temp->moveTo(position.x, position.y);
			temp->movePivot(pivot.x, pivot.y);
			objects.push_back(temp);
			if (temp->isRGB) {
				temp->loadRGBTexture(red, green, blue);
			} else if (temp->imgPath != "0") {
				temp->loadTexture(temp->imgPath);
			}
			temp->moveTo(position.x, position.y);
			temp->movePivot(pivot.x, pivot.y);
			break;
		}
		case 1: { //DisplayObject
			DisplayObject *temp = new DisplayObject();
			int speed;
			double scaleX;
			double scaleY;
			double rotation;
			double rotationAmount;
			int alpha;
			SDL_Point pivot, position;
			i >> temp->id >> temp->imgPath >> temp->red >> temp->green
					>> temp->blue >> std::boolalpha >> temp->vis
					>> std::boolalpha >> temp->isRGB >> temp->w >> temp->h
					>> speed >> scaleX >> scaleY >> rotation >> rotationAmount
					>> alpha >> pivot.x >> pivot.y >> position.x >> position.y;
			temp->setSpeed(speed);
			temp->setScale(scaleX, scaleY);
			temp->setRotationValue(rotation);
			temp->setRotation(rotationAmount);
			temp->setAlpha(alpha);
			temp->moveTo(position.x, position.y);
			temp->movePivot(pivot.x, pivot.y);
			objects.push_back(temp);
			if (temp->isRGB) {
				temp->loadRGBTexture(red, green, blue);
			} else if (temp->imgPath != "") {
				temp->loadTexture(temp->imgPath);
			}
			temp->moveTo(position.x, position.y);
			temp->movePivot(pivot.x, pivot.y);
			break;
		}
		case 2: { //DisplayObjectContainer
			DisplayObjectContainer *temp = new DisplayObjectContainer();
			int speed;
			double scaleX;
			double scaleY;
			double rotation;
			double rotationAmount;
			int alpha;
			SDL_Point pivot, position;
			i >> temp->id >> temp->imgPath >> temp->red >> temp->green
					>> temp->blue >> std::boolalpha >> temp->vis
					>> std::boolalpha >> temp->isRGB >> temp->w >> temp->h
					>> speed >> scaleX >> scaleY >> rotation >> rotationAmount
					>> alpha >> pivot.x >> pivot.y >> position.x >> position.y;
			temp->setSpeed(speed);
			temp->setScale(scaleX, scaleY);
			temp->setRotationValue(rotation);
			temp->setRotation(rotationAmount);
			temp->setAlpha(alpha);
			temp->moveTo(position.x, position.y);
			temp->movePivot(pivot.x, pivot.y);
			objects.push_back(temp);
			if (temp->isRGB) {
				temp->loadRGBTexture(red, green, blue);
			} else if (temp->imgPath != "") {
				temp->loadTexture(temp->imgPath);
			}
			temp->moveTo(position.x, position.y);
			temp->movePivot(pivot.x, pivot.y);
			break;
		}
		case 3: { //Sprite
			Sprite *temp = new Sprite();
			int speed;
			double scaleX;
			double scaleY;
			double rotation;
			double rotationAmount;
			int alpha;
			int x1, x2, y1, y2;
			i >> temp->id >> temp->imgPath >> temp->red >> temp->green
					>> temp->blue >> std::boolalpha >> temp->vis
					>> std::boolalpha >> temp->isRGB >> temp->w >> temp->h
					>> speed >> scaleX >> scaleY >> rotation >> rotationAmount
					>> alpha >> x1 >> y1 >> x2 >> y2;
			temp->setSpeed(speed);
			temp->setScale(scaleX, scaleY);
			temp->setRotationValue(rotation);
			temp->setRotation(rotationAmount);
			temp->setAlpha(alpha);
			temp->moveTo(x2, y2);
			temp->movePivot(x1, y1);
			objects.push_back(temp);
			if (temp->isRGB) {
				temp->loadRGBTexture(red, green, blue);
			} else if (temp->imgPath != "") {
				temp->loadTexture(temp->imgPath);
			}
			temp->moveTo(position.x, position.y);
			temp->movePivot(pivot.x, pivot.y);
			break;
		}
		case 4: { //AnimatedSprite (haven't added some fields yet - needs to be finished). 

			AnimatedSprite *temp = new AnimatedSprite();
			int speed;
			double scaleX;
			double scaleY;
			double rotation;
			double rotationAmount;
			int alpha;
			SDL_Point pivot, position;
			int num;
			i >> temp->id >> num;
			for (int Q = 0; Q < num; Q++) {

				string n, b, x;
				bool l, u;
				int f, r, s, e;
				i >> n >> b >> x >> std::boolalpha >> l >> std::boolalpha >> u
						>> f >> r >> s >> e;
				if (u) {
					temp->addAnimation(b, x, n, f, r, l);
				} else {
					temp->addAnimation(b, n, f, r, l);
				}
			}

			i >> std::boolalpha >> temp->vis >> temp->w >> temp->h >> speed
					>> scaleX >> scaleY >> rotation >> rotationAmount >> alpha
					>> pivot.x >> pivot.y >> position.x >> position.y;
			temp->setSpeed(speed);
			temp->setScale(scaleX, scaleY);
			temp->setRotationValue(rotation);
			temp->setRotation(rotationAmount);
			temp->setAlpha(alpha);
			temp->moveTo(position.x, position.y);
			temp->movePivot(pivot.x, pivot.y);
			objects.push_back(temp);
			temp->moveTo(position.x, position.y);
			temp->movePivot(pivot.x, pivot.y);
			break;
		}
		case 5: { //DemoSprite
			DemoSprite *temp = new DemoSprite();
			int speed;
			double scaleX;
			double scaleY;
			double rotation;
			double rotationAmount;
			int alpha;
			SDL_Point pivot, position;
			i >> temp->id >> temp->imgPath >> temp->red >> temp->green
					>> temp->blue >> std::boolalpha >> temp->vis
					>> std::boolalpha >> temp->isRGB >> temp->w >> temp->h
					>> speed >> scaleX >> scaleY >> rotation >> rotationAmount
					>> alpha >> pivot.x >> pivot.y >> position.x >> position.y;
			temp->setSpeed(speed);
			temp->setScale(scaleX, scaleY);
			temp->setRotationValue(rotation);
			temp->setRotation(rotationAmount);
			temp->setAlpha(alpha);
			temp->moveTo(position.x, position.y);
			cerr << "Position:" << position.x << ", " << position.y << "\n";
			temp->movePivot(pivot.x, pivot.y);
			objects.push_back(temp);
			if (temp->isRGB) {
				temp->loadRGBTexture(red, green, blue);
			} else if (temp->imgPath != "") {
				temp->loadTexture(temp->imgPath);
			}
			temp->moveTo(position.x, position.y);
			temp->movePivot(pivot.x, pivot.y);
			break;
		}
		case 6: { //Layer

			Layer *temp = new Layer();
			double s;
			i >> temp->id >> s;
			temp->setScale(s);
			objects.push_back(temp);
			break;
		}
		case 7: { //Player

			Player *temp = Player::getPlayer();
			SDL_Point position;
			i >> position.x >> position.y;
			temp->moveTo(position.x, position.y);
			temp->setHitbox(.1, .9);
			temp->showHitbox = true;
			objects.push_back(temp);
			break;
		}
		case 8: { //Door
			Door *temp = new Door();
			int speed;
			double scaleX;
			double scaleY;
			double rotation;
			double rotationAmount;
			int alpha;
			SDL_Point pivot, position;
			i >> temp->id >> temp->imgPath >> temp->red >> temp->green
					>> temp->blue >> std::boolalpha >> temp->vis
					>> std::boolalpha >> temp->isRGB >> temp->w >> temp->h
					>> speed >> scaleX >> scaleY >> rotation >> rotationAmount
					>> alpha >> pivot.x >> pivot.y >> position.x >> position.y;
			temp->setSpeed(speed);
			temp->setScale(scaleX, scaleY);
			temp->setRotationValue(rotation);
			temp->setRotation(rotationAmount);
			temp->setAlpha(alpha);
			temp->moveTo(position.x, position.y);
			temp->movePivot(pivot.x, pivot.y);
			objects.push_back(temp);
			if (temp->isRGB) {
				temp->loadRGBTexture(red, green, blue);
			} else if (temp->imgPath != "") {
				temp->loadTexture(temp->imgPath);
			}
			temp->moveTo(position.x, position.y);
			temp->movePivot(pivot.x, pivot.y);
			temp->type = "door";
			break;
		}
		case 9: { //Object
			Object *temp = new Object();
			int speed;
			double scaleX;
			double scaleY;
			double rotation;
			double rotationAmount;
			int alpha;
			SDL_Point pivot, position;
			i >> temp->id >> temp->imgPath >> temp->red >> temp->green
					>> temp->blue >> std::boolalpha >> temp->vis
					>> std::boolalpha >> temp->isRGB >> temp->w >> temp->h
					>> speed >> scaleX >> scaleY >> rotation >> rotationAmount
					>> alpha >> pivot.x >> pivot.y >> position.x >> position.y
					>> temp->boundLowX >> temp->boundHighX >> temp->boundLowY
					>> temp->boundHighY;
			temp->setSpeed(speed);
			temp->setScale(scaleX, scaleY);
			temp->setRotationValue(rotation);
			temp->setRotation(rotationAmount);
			temp->setAlpha(alpha);
			temp->moveTo(position.x, position.y);
			temp->movePivot(pivot.x, pivot.y);
			objects.push_back(temp);
			if (temp->isRGB) {
				temp->loadRGBTexture(red, green, blue);
			} else if (temp->imgPath != "") {
				temp->loadTexture(temp->imgPath);
			}
			temp->moveTo(position.x, position.y);
			temp->movePivot(pivot.x, pivot.y);
			temp->hitbox();
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

		for (vector<DisplayObject*>::iterator it = objects.begin();
				it != objects.end(); it++) {
			if (id1 == (*it)->id) {
				temp1 = (DisplayObjectContainer*) (*it);
			}
		}

		for (vector<DisplayObject*>::iterator it = objects.begin();
				it != objects.end(); it++) {
			if (id2 == (*it)->id) {
				temp2 = *it;
			}
		}
		temp1->addChild(temp2);
	}

}

void Scene::saveScene(string sceneFilePath) {

	vector < string > objects;
	vector < string > dependencies;
	string desc;
	stringstream sstm;
	long px0 = pivot.x, px1 = position.x, py0 = pivot.y, py1 = position.y;
	sstm << "0 " << id << " " << imgPath << " " << red << " " << green << " "
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
	std::ofstream o(sceneFilePath);
	o << objects.size() << " " << dependencies.size() << std::endl;
	for (string object : objects) {
		o << object;
	}
	for (string dependency : dependencies) {
		o << dependency;
	}

}

void Scene::update(set<SDL_Scancode> pressedKeys) {
	DisplayObjectContainer::update(pressedKeys);
}
void Scene::draw(AffineTransform &at) {
	DisplayObjectContainer::draw(at);
}
