/*
  kiss_sdl widget toolkit
  Copyright (c) 2016 Tarvo Korrovits <tkorrovi@mail.com>

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would
     be appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not
     be misrepresented as being the original software.
  3. This notice may not be removed or altered from any source
     distribution.

  kiss_sdl version 1.2.0
*/

#include "FileBrowser.h"
#include <iostream>
using namespace std;

DevLoop* FileBrowser::running_dev_tool;

FileBrowser::FileBrowser(kiss_array &objects, int width, int height,
	int parent_width, int parent_height, kiss_window* window, DevLoop* running_tool){
	quit = 0;
	draw = 1;
	this->width = width;
	this->height = height;

	textbox_width = 250;
	textbox_height = 250;

	kiss_button_new(&load_scene_button, window, "Load Scene", 5, 5);
	kiss_button_new(&save_scene_button, window, "Save Scene", 15 + load_scene_button.rect.w, 5);
	kiss_button_new(&set_background_button, window, "Load BG",
		85 + save_scene_button.rect.w, 5);

	// renderer = kiss_init("browser", &objects, 640, 480);
	this->objects=&objects;

	kiss_array_new(&a1);
	kiss_array_append(this->objects, ARRAY_TYPE, &a1);
	kiss_array_new(&a2);
	kiss_array_append(this->objects, ARRAY_TYPE, &a2);

	/* Arrange the widgets nicely relative to each other */
	kiss_window_new(&window1, NULL, 1, parent_width/2-width/2,
		parent_height/2-height/2, width, height);
	kiss_textbox_new(&textbox1, &window1, 1, &a1, parent_width/2 -
		(2 * textbox_width + 2 * kiss_up.w - kiss_edge) / 2,
		parent_height/2-textbox_height/2-2*kiss_normal.h, textbox_width, textbox_height);
	kiss_vscrollbar_new(&vscrollbar1, &window1, textbox1.rect.x +
		textbox_width, textbox1.rect.y, textbox_height);
	kiss_textbox_new(&textbox2, &window1, 1, &a2,
		vscrollbar1.uprect.x + kiss_up.w, textbox1.rect.y,
		textbox_width, textbox_height);
	kiss_vscrollbar_new(&vscrollbar2, &window1, textbox2.rect.x +
		textbox_width, vscrollbar1.uprect.y, textbox_height);
	kiss_label_new(&label1, &window1, "Folders", textbox1.rect.x +
		kiss_edge, textbox1.rect.y - kiss_textfont.lineheight);
	kiss_label_new(&label2, &window1, "Files", textbox2.rect.x +
		kiss_edge, textbox1.rect.y - kiss_textfont.lineheight);
	kiss_label_new(&label_sel, &window1, "", textbox1.rect.x +
		kiss_edge, textbox1.rect.y + textbox_height +
		kiss_normal.h);
	kiss_entry_new(&entry, &window1, 1, "kiss", textbox1.rect.x,
		label_sel.rect.y + kiss_textfont.lineheight,
		2 * textbox_width + 2 * kiss_up.w + kiss_edge);
	kiss_button_new(&button_cancel, &window1, "Cancel",
		entry.rect.x + entry.rect.w - kiss_edge - kiss_normal.w,
		entry.rect.y + entry.rect.h + kiss_normal.h);
	kiss_button_new(&button_ok1, &window1, "OK", button_cancel.rect.x -
		2 * kiss_normal.w, button_cancel.rect.y);

	dirent_read(&textbox1, &vscrollbar1, &textbox2, &vscrollbar2,
		&label_sel);
	/* Do that, and all widgets associated with the window will show */
	window1.visible = 0;

	running_dev_tool = running_tool;
	current_scene_path = "";
	current_scene = (Scene*) running_dev_tool->children[SCENE_DOC_INDEX];
	kiss_getcwd(home_dir, KISS_MAX_LENGTH*4);
	load = false;
	add_bg = false;
}

FileBrowser::~FileBrowser(){
	kiss_clean(this->objects);
}

void FileBrowser::visible(){
	window1.visible = 1;
}

void FileBrowser::invisible(){
	window1.visible = 0;
}

void FileBrowser::text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar)
{
	qsort(textbox->array->data, textbox->array->length, sizeof(void *),
		kiss_string_compare);
	vscrollbar->step = 0.;
	if (textbox->array->length - textbox->maxlines > 0)
		vscrollbar->step = 1. / (textbox->array->length -
			textbox->maxlines);
	textbox->firstline = 0;
	textbox->highlightline = -1;
	vscrollbar->fraction = 0.;
}

/* Read directory entries into the textboxes */
void FileBrowser::dirent_read(kiss_textbox *textbox1, kiss_vscrollbar *vscrollbar1,
	kiss_textbox *textbox2,	kiss_vscrollbar *vscrollbar2,
	kiss_label *label_sel)
{
	kiss_dirent *ent;
	kiss_stat s;
	kiss_dir *dir;
	char buf[KISS_MAX_LENGTH], ending[2];

	kiss_array_free(textbox1->array);
	kiss_array_free(textbox2->array);
	kiss_array_new(textbox1->array);
	kiss_array_new(textbox2->array);
	kiss_getcwd(buf, KISS_MAX_LENGTH);
	kiss_getcwd(curr_dir, KISS_MAX_LENGTH*4);
	strcpy(ending, "/");
	if (buf[0] == 'C') strcpy(ending, "\\");
	if (!strcmp(buf, "/") || !strcmp(buf, "C:\\")) strcpy(ending, "");
	kiss_string_copy(label_sel->text, (2 * textbox1->rect.w +
		2 * kiss_up.w) / kiss_textfont.advance, buf, ending);
#ifdef _MSC_VER
	dir = kiss_opendir("*");
#else
	dir = kiss_opendir(".");
#endif
	while ((ent = kiss_readdir(dir))) {
		if (!ent->d_name) continue;
		kiss_getstat(ent->d_name, &s);
		if (kiss_isdir(s))
			kiss_array_appendstring(textbox1->array, 0,
				ent->d_name, "/");
		else if (kiss_isreg(s))
			kiss_array_appendstring(textbox2->array, 0,
				ent->d_name, NULL);
	}
	kiss_closedir(dir);
	text_reset(textbox1, vscrollbar1);
	text_reset(textbox2, vscrollbar2);
}

/* The widget arguments are widgets that this widget talks with */
void FileBrowser::textbox1_event(kiss_textbox *textbox, SDL_Event *e,
	kiss_vscrollbar *vscrollbar1, kiss_textbox *textbox2,
	kiss_vscrollbar *vscrollbar2, kiss_label *label_sel, int *draw)
{
	int index;

	if (kiss_textbox_event(textbox, e, draw)) {
		index = textbox->firstline + textbox->selectedline;
		if (strcmp((char *) kiss_array_data(textbox->array, index),
			"")) {
			textbox->selectedline = -1;
			kiss_chdir((char *) kiss_array_data(textbox->array,
				index));
			dirent_read(textbox, vscrollbar1, textbox2,
				vscrollbar2, label_sel);
			*draw = 1;
		}
	}
}

void FileBrowser::vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e,
	kiss_textbox *textbox1, int *draw)
{
	int firstline;

	if (kiss_vscrollbar_event(vscrollbar, e, draw) &&
		textbox1->array->length - textbox1->maxlines > 0) {
		firstline = (int) ((textbox1->array->length - 
			textbox1->maxlines) * vscrollbar->fraction + 0.5);
		if (firstline >= 0) textbox1->firstline = firstline;
		*draw = 1;
	}
}

void FileBrowser::textbox2_event(kiss_textbox *textbox, SDL_Event *e,
	kiss_vscrollbar *vscrollbar2, kiss_entry *entry, int *draw)
{
	int index;

	if (kiss_textbox_event(textbox, e, draw)) {
		index = textbox->firstline + textbox->selectedline;
		if (strcmp((char *) kiss_array_data(textbox->array, index),
			"")) {
			kiss_string_copy(entry->text,
				entry->textwidth / kiss_textfont.advance,
				(char *) kiss_array_data(textbox->array,
				index), NULL);
			*draw = 1;
		}
	}
}

void FileBrowser::vscrollbar2_event(kiss_vscrollbar *vscrollbar, SDL_Event *e,
	kiss_textbox *textbox2, int *draw)
{
	int firstline;

	if (kiss_vscrollbar_event(vscrollbar, e, draw) &&
		textbox2->array->length) {
		firstline = (int) ((textbox2->array->length - 
			textbox2->maxlines) * vscrollbar->fraction + 0.5);
		if (firstline >= 0) textbox2->firstline = firstline;
		*draw = 1;
	}
}

void FileBrowser::button_ok1_event(kiss_button *button, SDL_Event *e,
	kiss_window *window1, kiss_label *label_sel,
	kiss_entry *entry, int *draw)
{

	if (kiss_button_event(button, e, draw)) {
		if(chdir(home_dir) < 0)
			cerr << "Failed to reset directory!" << endl;

		if(load)				load_scene_from_path();
		else if(!add_bg)		save_scene_from_path();
		else if(add_bg)			set_bg_from_path();
	}
}

void FileBrowser::button_cancel_event(kiss_button *button, SDL_Event *e,
	int *quit, int *draw)
{
	if (kiss_button_event(button, e, draw))
		close();
}

void FileBrowser::event(SDL_Event *event, int *draw){
	if(kiss_button_event(&load_scene_button, event, draw)){
		load = true;
		add_bg = false;
		open();
	}
	if(kiss_button_event(&save_scene_button, event, draw)){
		load = false;
		add_bg = false;
		open();
	}
	if(kiss_button_event(&set_background_button, event, draw)){
		load = false;
		add_bg = true;
		open();
	}
	kiss_window_event(&window1, event, draw);
	textbox1_event(&textbox1, event, &vscrollbar1, &textbox2, &vscrollbar2, &label_sel, draw);
	vscrollbar1_event(&vscrollbar1, event, &textbox1, draw);
	textbox2_event(&textbox2, event, &vscrollbar2, &entry, draw);
	vscrollbar2_event(&vscrollbar2, event, &textbox2, draw);
	button_cancel_event(&button_cancel, event, &quit, draw);

	kiss_entry_event(&entry, event, draw);

	button_ok1_event(&button_ok1, event, &window1,
		&label_sel, &entry, draw);
	vscrollbar1_event(&vscrollbar1, NULL, &textbox1, draw);
	vscrollbar2_event(&vscrollbar2, NULL, &textbox2, draw);
}

void FileBrowser::draw_items(SDL_Renderer *renderer){
	kiss_window_draw(&window1, renderer);
	kiss_label_draw(&label1, renderer);
	kiss_label_draw(&label2, renderer);
	kiss_textbox_draw(&textbox1, renderer);
	kiss_vscrollbar_draw(&vscrollbar1, renderer);
	kiss_textbox_draw(&textbox2, renderer);
	kiss_vscrollbar_draw(&vscrollbar2, renderer);
	kiss_label_draw(&label_sel, renderer);
	kiss_entry_draw(&entry, renderer);
	kiss_button_draw(&button_ok1, renderer);
	kiss_button_draw(&button_cancel, renderer);
	kiss_button_draw(&save_scene_button, renderer);
	kiss_button_draw(&load_scene_button, renderer);
	kiss_button_draw(&set_background_button, renderer);
}

void FileBrowser::open(){
	if(chdir(curr_dir) < 0)
		cerr << "could not return to previous directory" << endl;
	window1.visible = 1;
	running_dev_tool->disable_input = true;
}

void FileBrowser::close(){
	if(chdir(home_dir) < 0)
		cerr << "could not return to home directory!" << endl;
	window1.visible = 0;
	running_dev_tool->disable_input = false;
	strcpy(entry.text, "Enter Path");
}

void FileBrowser::load_scene_from_path(){
	string tmp = string(curr_dir) + "/" +string(entry.text);
	char* path = (char*) tmp.c_str();
	ifstream i(path);

	if(i.good()){
		i.close();
		// Camera* camera = running_dev_tool->camera;
		Scene *scene = new Scene();
		scene->setRenderer(running_dev_tool->renderer);
		printf("LOADING NEW SCENE!\n");
		scene->loadScene(path);
		delete running_dev_tool->children[SCENE_DOC_INDEX];
		running_dev_tool->children[SCENE_DOC_INDEX] = scene;
		// camera->removeScene(current_scene);
		// camera->addScene(scene);
		current_scene_path = string(curr_dir) + entry.text;
		current_scene = scene;
		strcpy(entry.text, "Enter Scene Path");

		close();
	}
	else{
		i.close();
		window1.bg = {220,20,60};
	}
}

void FileBrowser::save_scene_from_path(){
	current_scene_path = string(curr_dir) + "/" + string(entry.text);
	current_scene = ((Scene*)running_dev_tool->children[SCENE_DOC_INDEX]);
	current_scene->saveScene(current_scene_path);
	strcpy(entry.text, "Enter Scene Path");
	// ((Scene*) running_dev_tool->children[SCENE_DOC_INDEX])->saveScene(current_scene_path);
	close();
}

void FileBrowser::set_bg_from_path(){
	string tmp = string(curr_dir) + "/" + string(entry.text);
	char* path = (char*) tmp.c_str();
	SDL_Surface* img = IMG_Load(path);

	if(img == NULL){
		window1.bg = {220,20,60};
		return;
	}

	current_scene->setImage(img);
	current_scene->imgPath = tmp;
	strcpy(entry.text, "Enter Scene Path");
	// running_dev_tool->children[SCENE_DOC_INDEX]->setImage(img);

	close();
}