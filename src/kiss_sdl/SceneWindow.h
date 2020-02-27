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
	void event(SDL_Event *event, int* draw, kiss_window& wdw, kiss_window& dir_wdw);
	kiss_window window = {0};
	kiss_button load_scene_button = {0};
private:
	void load_scene_event(kiss_window& wdw, kiss_window& dir_wdw);
};

#endif