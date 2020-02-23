#ifndef DEVTOOL_H
#define DEVTOOL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "AnimatedSprite.h"
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include "Scene.h"
#include "ResourceBar.h"

using namespace std;

class DevTool : public Game{
public:
	DevTool();
	virtual ~DevTool();
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
private:
	ResourceBar* resourceBar;
};

#endif
