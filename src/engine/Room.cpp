#include "Room.h"

Room::Room(string scene):DisplayObjectContainer() {
	cerr << "constructing-1\n";
	room = new Scene();
	cerr << "constructing0\n";
	room->loadScene(scene);
	cerr << "constructing1\n";
}

void Room::update(set<SDL_Scancode> pressedKeys) {
	if (active)
		room->update(pressedKeys);
}

void Room::draw(AffineTransform &at) {
	DisplayObjectContainer::applyTransformations(at);
	if (visable)
		room->draw(at);
	DisplayObjectContainer::reverseTransformations(at);

}
