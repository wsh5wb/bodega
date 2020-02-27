#include "ItemBar.h"

ItemBar::ItemBar(){

}

ItemBar::ItemBar(kiss_window * wdw){
	window = wdw;
	//kiss_entry_new(&xPosEntry,Game::window,0,"0",20,20,30);
	SDL_Color lightGrey = {180,180,180};
	kiss_entry_new(&xPosEntry,wdw,0,"0",kiss_screen_width*4/5 + 100,20,20);
	kiss_label_new(&xPosLabel,wdw,"xPos:",kiss_screen_width*4/5 + 20,20);
	//xPosEntry.bg = lightGrey; //xPosLabel.bg = lightGrey;
}

ItemBar::~ItemBar(){
	
}

void ItemBar::event(SDL_Event *event, int* draw){
	kiss_entry_event(&xPosEntry,event,draw);

}


void ItemBar::draw(SDL_Renderer *renderer){
	//kiss_entry_draw(&xPosEntry,Game::renderer);
	kiss_label_draw(&xPosLabel,renderer);
	kiss_entry_draw(&xPosEntry,renderer);
}