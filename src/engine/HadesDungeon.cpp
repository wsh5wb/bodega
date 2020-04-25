#include "HadesDungeon.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

HadesDungeon::HadesDungeon(){

	id = "HadesDungeon";

	basic_rooms_size = 9;
	portal_index = 10;
	int basic_rooms0[] = { 0, 2, 3, 4, 5 ,6 ,7 ,8 ,9 };
	basic_rooms = (int*)malloc(sizeof(int)*basic_rooms_size);
	for(int i = 0;i<basic_rooms_size;i++){
		basic_rooms[i] = basic_rooms0[i];
	}
	hades_theme.loadMusic("./resources/sounds/lullaby.wav");
	hades_theme.playMusic();
	scenes.push_back("./resources/scenes/hades?/basic_room.txt");
	scenes.push_back("./resources/scenes/hades?/start.txt");
	scenes.push_back("./resources/scenes/hades?/basic_room2.txt");
	scenes.push_back("./resources/scenes/hades?/lava_statue.txt");
	scenes.push_back("./resources/scenes/hades?/lava_chest.txt");
	scenes.push_back("./resources/scenes/hades?/jelly_room.txt");
	scenes.push_back("./resources/scenes/hades?/single_jelly_room.txt");
	scenes.push_back("./resources/scenes/hades?/double_jelly_room.txt");
	scenes.push_back("./resources/scenes/hades?/four_lava_jelly_room.txt");
	scenes.push_back("./resources/scenes/hades?/urchin_room.txt");
	scenes.push_back("./resources/scenes/hades?/portal_room.txt");
	// these must go at bottom
	scenes.push_back("./resources/scenes/hades?/boss_top_left.txt");
	scenes.push_back("./resources/scenes/hades?/boss_top_right.txt");
	scenes.push_back("./resources/scenes/hades?/boss_bot_left.txt");
	scenes.push_back("./resources/scenes/hades?/boss_bot_right.txt");
}

HadesDungeon::~HadesDungeon() {
	free(basic_rooms);
}

void HadesDungeon::update(set<SDL_Scancode> pressedKeys) {
	Dungeon::update(pressedKeys);
}
void HadesDungeon::draw(AffineTransform &at) {
	Dungeon::draw(at);
}

void HadesDungeon::generate() {
	Dungeon::generate();
}
