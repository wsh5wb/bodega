#include "Camera.h"
#include <iostream>

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
	x += dx;
	y += dy;
}
void Camera::zoom(double x, double y) {
	viewportWidth = (int) (x * viewportWidth);
	viewportHeight = (int) (y * viewportHeight);
}

void Camera::setLocation(int newX, int newY) {
	x = newX;
	y = newY;
}
void Camera::setZoom(double w, double h) {
	viewportWidth = w;
	viewportHeight = h;
}

void Camera::update(set<SDL_Scancode> pressedKeys) {
	cout << x << " " << y << endl;
	for (SDL_Scancode code : pressedKeys){
		switch(code){
			case SDL_SCANCODE_W:
				pan(0,-10);
				break;
			case SDL_SCANCODE_A:
				pan(-10,0);
				break;
			case SDL_SCANCODE_S:
				pan(0,10);
				break;
			case SDL_SCANCODE_D:
				pan(10,0);
				break;
			case SDL_SCANCODE_Z:
				zoom(1.1, 1.1);
				break;
			case SDL_SCANCODE_X:
				zoom(.9,.9);
				break;
		}
	}

	container->moveTo(-x, -y);
	container->movePivot(-viewportWidth/2, -viewportHeight/2);
	container->setScale(1.0 * viewportWidth / 500.0,
			1.0 * viewportHeight / 500.0);
	container->update(pressedKeys);
}
void Camera::draw(AffineTransform &at) {
	container->draw(at);
}