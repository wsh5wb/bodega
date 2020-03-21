#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "DevLoop.h"
#include "definitions.h"
#include "../kiss/kiss_sdl.h"
#include "../../src/engine/DisplayObjectContainer.h"
#include "../../src/engine/Scene.h"

using namespace std;

class FileBrowser{
public:
	FileBrowser(kiss_array &objects, int width, int height, int parent_width, int parent_height,
		kiss_window* window, DevLoop* running_tool);
	~FileBrowser();

	void visible();
	void invisible();
	int getStatus();
	string getPath();

	void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);
	void dirent_read(kiss_textbox *textbox1, kiss_vscrollbar *vscrollbar1,
		kiss_textbox *textbox2,	kiss_vscrollbar *vscrollbar2,
		kiss_label *label_sel);

	void textbox1_event(kiss_textbox *textbox, SDL_Event *e,
		kiss_vscrollbar *vscrollbar1, kiss_textbox *textbox2,
		kiss_vscrollbar *vscrollbar2, kiss_label *label_sel, int *draw);
	void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e,
		kiss_textbox *textbox1, int *draw);
	void textbox2_event(kiss_textbox *textbox, SDL_Event *e,
		kiss_vscrollbar *vscrollbar2, kiss_entry *entry, int *draw);
	void vscrollbar2_event(kiss_vscrollbar *vscrollbar, SDL_Event *e,
		kiss_textbox *textbox2, int *draw);
	void button_ok1_event(kiss_button *button, SDL_Event *e,
		kiss_window *window1, kiss_label *label_sel,
		kiss_entry *entry, int *draw);
	void button_cancel_event(kiss_button *button, SDL_Event *e,
		int *quit, int *draw);

	void draw_items(SDL_Renderer *renderer);
	void event(SDL_Event *event, int *draw);
	
private:
	void load_scene_from_path();
	void save_scene_from_path();
	void set_bg_from_path();
	void close();
	void open();

	SDL_Event e;
	kiss_window window1;
	kiss_array a1, a2;
	kiss_array* objects;
	kiss_label label1 = {0}, label2 = {0}, label_sel = {0};
	kiss_button button_ok1 = {0}, button_cancel = {0};
	kiss_button save_scene_button = {0};
	kiss_button load_scene_button = {0};
	kiss_button set_background_button = {0};
	kiss_textbox textbox1 = {0}, textbox2 = {0};
	kiss_vscrollbar vscrollbar1 = {0}, vscrollbar2 = {0};
	kiss_entry entry = {0};
	int textbox_width, textbox_height, draw, quit,
	width, height;

	char curr_dir[KISS_MAX_LENGTH*4];
	char home_dir[KISS_MAX_LENGTH*4];
	
	static DevLoop * running_dev_tool;
	Scene* current_scene;
	string current_scene_path;
	FileBrowser* browser;
	
	//TODO: Make these into one enum for readability
	bool load;
	bool add_bg;
};

#endif