// #include "SceneWindow.h"
// #include "DevTool.h"
// #include <iostream>

// DevLoop* SceneWindow::running_dev_tool;

// SceneWindow::SceneWindow(int parent_width, int parent_height, kiss_window* window, DevLoop* running_tool,
// 	kiss_array &objects){

// 	int dialogue_height = parent_height/5;
// 	int dialogue_width = parent_width/3;
// 	int window_start_x = parent_width/2 - dialogue_width/2;
// 	int window_start_y = parent_height/2 - dialogue_height/2;
// 	int entry_width = dialogue_width*8/10;
// 	int entry_start_x = dialogue_width/2 - entry_width/2 + window_start_x;
// 	int entry_start_y = dialogue_height/2 - kiss_textfont.lineheight + window_start_y;

// 	this->window = window;

// 	kiss_window_new(&scene_dialogue_window, NULL, 1, window_start_x, window_start_y,
// 		dialogue_width, dialogue_height);
// 	scene_dialogue_window.visible = 0;
// 	scene_dialogue_window.bg = {64,64,64};

// 	kiss_button_new(&load_scene_button, window, "Load Scene", 5, 5);
// 	kiss_button_new(&save_scene_button, window, "Save Scene", 15 + load_scene_button.rect.w, 5);
// 	kiss_button_new(&set_background_button, window, "Load BG",
// 		85 + save_scene_button.rect.w, 5);
// 	kiss_button_new(&close_screen_button, &scene_dialogue_window, "X", 
// 		window_start_x+5, window_start_y+5);

// 	kiss_entry_new(&scene_path_entry, &scene_dialogue_window, 1, "Enter Scene Path",
// 		entry_start_x, entry_start_y, entry_width);

// 	running_dev_tool = running_tool;
// 	current_scene_path = "";
// 	current_scene = (Scene*) running_dev_tool->children[SCENE_DOC_INDEX];
// 	load = false;
// 	add_bg = false;
// 	browser = new FileBrowser(objects, 640, 480, parent_width, parent_height);
// }

// SceneWindow::~SceneWindow(){
// 	delete browser;
// }

// void SceneWindow::draw(SDL_Renderer *renderer){
// 	kiss_window_draw(&scene_dialogue_window, renderer);
// 	kiss_entry_draw(&scene_path_entry, renderer);

// 	kiss_button_draw(&save_scene_button, renderer);
// 	kiss_button_draw(&load_scene_button, renderer);
// 	kiss_button_draw(&close_screen_button, renderer);
// 	kiss_button_draw(&set_background_button, renderer);
// 	browser->draw_items(renderer);
// }

// void SceneWindow::event(SDL_Event *event, int* draw){
// 	if(kiss_button_event(&load_scene_button, event, draw)){
// 		load = true;
// 		add_bg = false;
// 		display_dialogue_window();
// 	}
// 	if(kiss_button_event(&save_scene_button, event, draw)){
// 		load = false;
// 		add_bg = false;
// 		display_dialogue_window();
// 	}
// 	kiss_window_event(&scene_dialogue_window, event, draw);
// 	if(kiss_entry_event(&scene_path_entry, event, draw)){
// 		if(load)				load_scene_from_path();
// 		else if(!add_bg)		save_scene_from_path();
// 		else if(add_bg)			set_bg_from_path();
// 	}
// 	if(kiss_button_event(&close_screen_button, event, draw)){
// 		close_dialogue_window();
// 	}
// 	if(kiss_button_event(&set_background_button, event, draw)){
// 		add_bg = true;
// 		display_dialogue_window();
// 	}
// 	browser->event(event, draw);

// }

// void SceneWindow::display_dialogue_window(){
// 	scene_dialogue_window.bg = {64,64,64};
// 	scene_dialogue_window.visible = 1;
// 	browser->visible();
// 	running_dev_tool->disable_input = true;
// }

// void SceneWindow::close_dialogue_window(){
// 	browser->invisible();
// 	scene_dialogue_window.visible = 0;
// 	running_dev_tool->disable_input = false;
// 	strcpy(scene_path_entry.text, "Enter Scene Path");
// }

// void SceneWindow::load_scene_from_path(){
// 	ifstream i(scene_path_entry.text);

// 	if(i.good()){
// 		// Camera* camera = running_dev_tool->camera;
// 		Scene *scene = new Scene();
// 		scene->setRenderer(running_dev_tool->renderer);
// 		scene->loadScene(scene_path_entry.text);
// 		delete running_dev_tool->children[SCENE_DOC_INDEX];
// 		running_dev_tool->children[SCENE_DOC_INDEX] = scene;
// 		// camera->removeScene(current_scene);
// 		// camera->addScene(scene);
// 		current_scene_path = scene_path_entry.text;
// 		current_scene = scene;
// 		scene_dialogue_window.visible = 0;
// 		strcpy(scene_path_entry.text, "Enter Scene Path");
// 		running_dev_tool->disable_input = false;
// 	}
// 	else
// 		scene_dialogue_window.bg = {220,20,60};// strcpy(scene_path_entry.text, "Enter valid path!");
// }

// void SceneWindow::save_scene_from_path(){
// 	current_scene_path = scene_path_entry.text;
// 	current_scene = ((Scene*)running_dev_tool->children[SCENE_DOC_INDEX]);
// 	current_scene->saveScene(current_scene_path);
// 	scene_dialogue_window.visible = 0;
// 	strcpy(scene_path_entry.text, "Enter Scene Path");
// 	running_dev_tool->disable_input = false;
// 	// ((Scene*) running_dev_tool->children[SCENE_DOC_INDEX])->saveScene(current_scene_path);
// }

// void SceneWindow::set_bg_from_path(){
// 	SDL_Surface* img = IMG_Load(scene_path_entry.text);

// 	if(img == NULL){
// 		scene_dialogue_window.bg = {220,20,60};
// 		return;
// 	}

// 	scene_dialogue_window.visible = 0;
// 	current_scene->setImage(img);
// 	running_dev_tool->disable_input = false;
// 	strcpy(scene_path_entry.text, "Enter Scene Path");
// 	// running_dev_tool->children[SCENE_DOC_INDEX]->setImage(img);
// }