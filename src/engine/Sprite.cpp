#include "Sprite.h"

Sprite::Sprite() {

}


Sprite::Sprite(string id, string filepath, bool particle) : DisplayObjectContainer(id,filepath,particle){

}

Sprite::Sprite(string id, int red, int green, int blue) :
		DisplayObjectContainer(id, red, green, blue) {

}

void Sprite::update(set<SDL_Scancode> pressedKeys) {
//	cout << "sprite";
}

void Sprite::draw(AffineTransform &at) {
	DisplayObjectContainer::draw(at);
}

void Sprite::saveSelf(vector<string> &objects, vector<string> &dependencies) {
	string desc;
	stringstream sstm;
	int px0 = pivot.x, px1 = position.x, py0 = pivot.y, py1 = position.y;
	sstm << "3 " << id << " " << imgPath << " " << red << " " << green << " "
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
