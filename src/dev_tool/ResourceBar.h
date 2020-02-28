#ifndef RESOURCEBAR_H
#define RESOURCEBAR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <filesystem>
#include "AnimatedSprite.h"
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include "Scene.h"
#include "ItemBar.h"
#include "Mouse.h"

#define SCENE_DOC_INDEX 0

class ResourceBar : public DisplayObjectContainer{
public:
	ResourceBar(int windowWidth, int windowHeight, DisplayObject *draggable, DisplayObjectContainer* mainwindow, ItemBar * bar);
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
};


#endif