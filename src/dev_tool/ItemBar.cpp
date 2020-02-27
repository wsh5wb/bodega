#include "ItemBar.h"
#include <iostream>

ItemBar::ItemBar(){

}

ItemBar::ItemBar(kiss_window * wdw){
	window = wdw;
	//kiss_entry_new(&xPosEntry,Game::window,0,"0",20,20,30);
	SDL_Color lightGrey = {180,180,180};
	int infoW = kiss_screen_width*4/5;

	kiss_label_new(&idLabel,wdw,"id:",infoW + 80,10);
	kiss_label_new(&xPosLabel,wdw,"xPos:",infoW + 20,45);
	kiss_label_new(&yPosLabel,wdw,"yPos:",infoW + 140,45);

	kiss_entry_new(&idEntry,wdw,0,"0", infoW + 105,5,90);
	kiss_entry_new(&xPosEntry,wdw,0,"0", infoW + 80,40,50);
	kiss_entry_new(&yPosEntry,wdw,0,"0", infoW + 190,40,50);


	//xPosEntry.bg = lightGrey; //xPosLabel.bg = lightGrey;
	idLabel.textcolor = kiss_white; xPosLabel.textcolor = kiss_white; yPosLabel.textcolor = kiss_white;
	//cout << infoW << xPosEntry.visible << " " << xPosEntry.textx << endl;
}

ItemBar::~ItemBar(){
	
}

void ItemBar::event(SDL_Event *event, int* draw){
	//xPosEntry.visible = 1;
	kiss_entry_event(&idEntry,event,draw);
	kiss_entry_event(&xPosEntry,event,draw);
	kiss_entry_event(&yPosEntry,event,draw);
	//cout << "event";

}


void ItemBar::draw(SDL_Renderer *renderer){
	kiss_label_draw(&idLabel,renderer);
	kiss_label_draw(&xPosLabel,renderer);
	kiss_label_draw(&yPosLabel,renderer);

	kiss_entry_draw(&idEntry,renderer);
	kiss_entry_draw(&xPosEntry,renderer);
	kiss_entry_draw(&yPosEntry,renderer);
}