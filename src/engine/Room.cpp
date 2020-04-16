#include "Room.h"

Room::Room(string scene):DisplayObjectContainer() {
	room = new Scene();
	room->loadScene(scene);
}

void Room::update(set<SDL_Scancode> pressedKeys) {
	if (active||start)
		room->update(pressedKeys);
}

void Room::draw(AffineTransform &at) {
	DisplayObjectContainer::applyTransformations(at);
	if (visable)
		room->draw(at);
	DisplayObjectContainer::reverseTransformations(at);

}
