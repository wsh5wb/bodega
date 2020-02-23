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
	ResourceBar();
	~ResourceBar();
private:
	DisplayObjectContainer menu;
};


#endif
