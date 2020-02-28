#ifndef DEVTOOL_H
#define DEVTOOL_H

#include "AffineTransform.h"
#include "AnimatedSprite.h"
#include "Animations.h"
#include "DisplayObjectContainer.h"
#include "DisplayObject.h"
#include "Game.h"
#include "jsonConversions.h"
#include "json.hpp"
#include "Mouse.h"
#include "Scene.h"
#include "Sprite.h"
#include "kiss_sdl.h"
#include "ItemBar.h"
#include "ResourceBar.h"

#define SCENE_DOC_INDEX 0

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using std::set;

class DevTool : public Game{
public:
	DevTool();
	virtual ~DevTool();
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

private:
	DisplayObject* draggable = NULL;
	ResourceBar *resourceBar;
	//ItemBar * infoBar;
};

#endif
