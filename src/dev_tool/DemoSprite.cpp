#include "DemoSprite.h"

DemoSprite::DemoSprite() {

}

DemoSprite::DemoSprite(string id, string filepath) :
		Sprite(id, filepath) {

}

DemoSprite::DemoSprite(string id, int red, int green, int blue) :
		Sprite(id, red, green, blue) {

}

void DemoSprite::update(set<SDL_Scancode> pressedKeys) {

	// for (SDL_Scancode code : pressedKeys) {
	// 	switch (code) {

	// 	case SDL_SCANCODE_DOWN: {
	// 		Sprite::translateDown();
	// 		break;
	// 	}
	// 	case SDL_SCANCODE_UP: {
	// 		Sprite::translateUp();
	// 		break;
	// 	}
	// 	case SDL_SCANCODE_LEFT: {
	// 		Sprite::translateLeft();
	// 		break;
	// 	}
	// 	case SDL_SCANCODE_RIGHT: {
	// 		Sprite::translateRight();
	// 		break;
	// 	}
	// 	case SDL_SCANCODE_Q: {
	// 		Sprite::scaleOut();
	// 		break;
	// 	}
	// 	case SDL_SCANCODE_W: {
	// 		Sprite::scaleIn();
	// 		break;
	// 	}
	// 	}
	// }
	Sprite::update(pressedKeys);

}

void DemoSprite::draw(AffineTransform &at) {
	Sprite::draw(at);
}

void DemoSprite::saveSelf(vector<string> &objects,
		vector<string> &dependencies) {
	string desc;
	stringstream sstm;
	long px0 = pivot.x, px1 = position.x, py0 = pivot.y, py1 = position.y;
	sstm << "5 " << id << " " << imgPath << " " << red << " " << green << " "
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