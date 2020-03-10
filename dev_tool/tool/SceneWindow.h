#ifndef SCENEWINDOW_H
#define SCENEWINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "definitions.h"
#include "DevLoop.h"
#include "../kiss/kiss_sdl.h"
#include "../../src/engine/DisplayObjectContainer.h"
#include "../../src/engine/Scene.h"

class SceneWindow{
public:
	SceneWindow(int parent_width, int parent_height, kiss_window* window, DevLoop* running_tool);
	void draw(SDL_Renderer *renderer);
	void event(SDL_Event *event, int* draw);

	kiss_window* window;
	kiss_window scene_dialogue_window;

	kiss_entry scene_path_entry;

	kiss_button save_scene_button = {0};
	kiss_button load_scene_button = {0};
	kiss_button set_background_button = {0};
	kiss_button close_screen_button = {0};
private:
	void display_dialogue_window();
	void close_dialogue_window();

	void load_scene_from_path();
	void save_scene_from_path();

	void set_bg_from_path();

	static DevLoop * running_dev_tool;
	Scene* current_scene;
	string current_scene_path;
	
	//TODO: Make these into one enum for readability
	bool load;
	bool add_bg;
};

#endif