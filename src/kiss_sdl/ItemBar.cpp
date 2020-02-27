#include "ItemBar.h"

ItemBar::ItemBar(){
	kiss_entry_new(&xPosEntry,Game::window,0,"0",20,20,30);
}

ItemBar::~ItemBar(){

}

void ItemBar::draw(AffineTransform &at){
	kiss_entry_draw(&xPosEntry,Game::renderer);
}