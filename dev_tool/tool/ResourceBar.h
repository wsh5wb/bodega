#ifndef RESOURCEBAR_H
#define RESOURCEBAR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <filesystem>
#include "definitions.h"
#include "ItemBar.h"
#include "../../src/engine/AnimatedSprite.h"
#include "../../src/engine/DisplayObject.h"
#include "../../src/engine/DisplayObjectContainer.h"
#include "../../src/engine/Sprite.h"
#include "../../src/engine/Scene.h"
#include "../../src/engine/Mouse.h"

class ResourceBar : public DisplayObjectContainer{
public:
	ResourceBar(int windowWidth, int windowHeight, DisplayObject *draggable, DisplayObjectContainer* mainwindow, ItemBar * bar, SDL_Renderer * renderer);
	~ResourceBar();
	void addChild(DisplayObject* child);
	void setMouseListener(Mouse* mouse);
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
private:
	DisplayObjectContainer* mainWindow;
	DisplayObjectContainer* menu;
	DisplayObject* drag;
	ItemBar * infoBar;
	int baseHeight;
	double windowHeight;
	double windowWidth;
	Mouse* mouseListener;
	int count;
	SDL_Renderer* renderer;
};


#endif