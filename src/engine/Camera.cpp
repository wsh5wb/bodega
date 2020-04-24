#include "Camera.h"

Camera *Camera::camera = 0;

Camera::Camera() {
	
}
Camera::~Camera() {

}

Camera* Camera::getCamera() {
	if (camera == 0) {
		camera = new Camera();
		camera->container = new DisplayObjectContainer();
		(camera->container)->id = "camera";
	}
	return camera;
}

void Camera::addScene(DisplayObject *child) {
	container->addChild(child);
}

void Camera::removeScene(DisplayObject *child) {
	container->removeImmediateChild(child);
}

void Camera::pan(int dx, int dy) {
	container->translate(-dx, -dy);
}
void Camera::zoom(double x, double y) {
	container->scaleX = x * (container->scaleX);
	container->scaleY = y * (container->scaleY);
}

void Camera::setLocation(int newX, int newY) {
	container->moveTo(-newX, -newY);
	//container->movePivot(-newX/2, -newY/2);
}
void Camera::setZoom(double w, double h) {
	container->setScale(1.0 * w / 500.0, 1.0 * h / 500.0);
}

void Camera::update(set<SDL_Scancode> pressedKeys) {
	container->update(pressedKeys);
}
void Camera::draw(AffineTransform &at) {
	container->draw(at);
}
