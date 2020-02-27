#include "SceneWindow.h"
#include <iostream>

SceneWindow::SceneWindow(int parent_width, int parent_height){
	int window_height = parent_height*3/4;
	int window_width = parent_width*3/5;

	kiss_window_new(&window, NULL, 1, parent_width/5, 0, 
		window_width, window_height);

	window.bg = kiss_black;

	kiss_button_new(&load_scene_button, &window, "Load Scene", parent_width/5 + 5,5);
	window.visible = 1;
}

void SceneWindow::draw(SDL_Renderer *renderer){
	kiss_window_draw(&window, renderer);
	kiss_button_draw(&load_scene_button, renderer);
}

void SceneWindow::event(SDL_Event *event, int* draw, kiss_window& wdw, kiss_window& dir_wdw){
	if(kiss_button_event(&load_scene_button, event, draw)){
		load_scene_event(wdw, dir_wdw);
	}
	kiss_window_event(&window, event, draw);
}

void SceneWindow::load_scene_event(kiss_window& wdw, kiss_window& dir_wdw){
	dir_wdw.visible = 1;
	dir_wdw.focus = 1;
	wdw.focus = 0;
}