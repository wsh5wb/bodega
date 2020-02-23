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

class ResourceBar : public DisplayObjectContainer{
public:
	ResourceBar(int windowWidth, int windowHeight);
	~ResourceBar();
	void addChild(DisplayObject* child);
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
private:
	DisplayObjectContainer* menu;
	double windowHeight;
	double windowWidth;
};


#endif
