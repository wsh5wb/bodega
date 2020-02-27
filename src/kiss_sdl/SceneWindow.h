#ifndef SCENEWINDOW_H
#define SCENEWINDOW_H

#include "kiss_sdl.h"
#include "DisplayObjectContainer.h"
#include "Game.h"
#include "Scene.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SceneWindow{
public:
	SceneWindow(int parent_width, int parent_height);
	void draw(SDL_Renderer *renderer);
	kiss_window window;
	kiss_button load_scene_button = {0};
private:

};

#endif