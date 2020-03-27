#ifndef DEVTOOL_H
#define DEVTOOL_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ItemBar.h"
#include "DevLoop.h"
#include "ResourceBar.h"
#include "definitions.h"
#include "../kiss/kiss_sdl.h"
#include "../../src/engine/AffineTransform.h"
#include "../../src/engine/AnimatedSprite.h"
#include "../../src/engine/Animations.h"
#include "../../src/engine/DisplayObjectContainer.h"
#include "../../src/engine/DisplayObject.h"
#include "../../src/engine/jsonConversions.h"
#include "../../src/engine/json.hpp"
#include "../../src/engine/Mouse.h"
#include "../../src/engine/Scene.h"
#include "../../src/engine/Sprite.h"

using std::set;

class DevTool : public DevLoop{
public:
	DevTool();
	virtual ~DevTool();
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	DisplayObject* leftClick(SDL_Point click_coords, DisplayObjectContainer * c);
	SDL_Point snapToGrid(SDL_Point coords);

private:
	DisplayObject* draggable = NULL;
	ResourceBar *resourceBar;
	bool makeParent = false;
	double gridSize;
};

#endif
