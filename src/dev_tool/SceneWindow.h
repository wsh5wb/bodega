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
	SceneWindow(int parent_width, int parent_height, kiss_window* window, Game* running_tool);
	void draw(SDL_Renderer *renderer);
	void event(SDL_Event *event, int* draw);
	kiss_window* window;
	kiss_window scene_dialogue_window;
	kiss_entry scene_path_entry;

	kiss_button save_scene_button = {0};
	kiss_button load_scene_button = {0};
private:
	void display_dialogue_window();
	void load_scene_from_path();
	void save_scene_from_path();

	static Game * running_dev_tool;
	string current_scene_path;
};

#endif