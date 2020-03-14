#include "ItemBar.h"
#include <iostream>
#include <stdlib.h>

ItemBar::ItemBar(){

}

ItemBar::ItemBar(kiss_window * wdw){
	window = wdw;
	curObj = NULL;

	int infoW = kiss_screen_width*4/5;

	//Labels
	kiss_label_new(&idLabel,wdw,"id:",infoW + 20,10);
	kiss_label_new(&xPosLabel,wdw,"xPos:",infoW + 20,45);
	kiss_label_new(&yPosLabel,wdw,"yPos:",infoW + 140,45);
	kiss_label_new(&xPivLabel,wdw,"xPiv:",infoW + 20,85);
	kiss_label_new(&yPivLabel,wdw,"yPiv:",infoW + 140,85);
	kiss_label_new(&xScaleLabel,wdw,"xScl:",infoW + 20,125);
	kiss_label_new(&yScaleLabel,wdw,"yScl:",infoW + 140,125);
	kiss_label_new(&rotLabel,wdw,"Rotation:",infoW + 20,165);
	kiss_label_new(&widthLabel,wdw,"Width: 0" ,infoW + 20,245);
	kiss_label_new(&heightLabel,wdw,"Height: 0",infoW + 140,245);
	kiss_label_new(&alphaLabel,wdw,"Alpha:", infoW + 20,205);
	kiss_label_new(&scaleLockLabel,wdw,"Lock Scale Ratio", infoW + 45,285);

	// Text Entries
	kiss_entry_new(&idEntry,wdw,0,"0", infoW + 55,5,185);
	kiss_entry_new(&xPosEntry,wdw,0,"0", infoW + 80,40,50);
	kiss_entry_new(&yPosEntry,wdw,0,"0", infoW + 190,40,50);
	kiss_entry_new(&xPivEntry,wdw,0,"0", infoW + 80,80,50);
	kiss_entry_new(&yPivEntry,wdw,0,"0", infoW + 190,80,50);
	kiss_entry_new(&xScaleEntry,wdw,0,"0", infoW + 80,120,50);
	kiss_entry_new(&yScaleEntry,wdw,0,"0", infoW + 190,120,50);
	kiss_entry_new(&rotEntry,wdw,0,"0", infoW + 125,160,80);
	kiss_entry_new(&alphaEntry,wdw,0,"255",infoW +100,200,50);

	// Buttons
	kiss_button_new(&delBut,wdw,"Delete",infoW + 170,650);
	kiss_button_new(&copyBut,wdw,"Copy",infoW + 90,650);
	kiss_selectbutton_new(&scaleLock,wdw,infoW + 20,285);

	idLabel.textcolor = kiss_white; xPosLabel.textcolor = kiss_white; yPosLabel.textcolor = kiss_white; scaleLockLabel.textcolor = kiss_white;
	xPivLabel.textcolor = kiss_white; yPivLabel.textcolor = kiss_white; rotLabel.textcolor = kiss_white; alphaLabel.textcolor = kiss_white;
	yScaleLabel.textcolor = kiss_white; xScaleLabel.textcolor = kiss_white; widthLabel.textcolor = kiss_white; heightLabel.textcolor = kiss_white;
}

ItemBar::~ItemBar(){
	
}

void ItemBar::initThisWindow(DisplayObjectContainer * win){
	thisWindow = win;
	this->renderer = win->getRenderer();
}

void ItemBar::setObj(DisplayObject *& obj){
	if(this == NULL){
		cout << "Item Bar is null";
		return;
	}
	curObj = obj;
	updateObjectFields();
}

void ItemBar::updateObjectFields(){
	if(curObj == NULL) {return;}
	scale = curObj->getScaleX()/curObj->getScaleY();
	strncpy(idEntry.text,curObj->getID().c_str(),sizeof(idEntry.text));
	strncpy(xPosEntry.text,to_string(curObj->getPosition().x).c_str(),sizeof(xPosEntry.text));
	strncpy(yPosEntry.text,to_string(curObj->getPosition().y).c_str(),sizeof(yPosEntry.text));
	strncpy(xPivEntry.text,to_string(curObj->getPivot().x).c_str(),sizeof(xPivEntry.text));
	strncpy(yPivEntry.text,to_string(curObj->getPivot().y).c_str(),sizeof(yPivEntry.text));
	strncpy(xScaleEntry.text,to_string(curObj->getScaleX()).substr(0,4).c_str(),sizeof(xScaleEntry.text));
	strncpy(yScaleEntry.text,to_string(curObj->getScaleY()).substr(0,4).c_str(),sizeof(yScaleEntry.text));
	strncpy(alphaEntry.text,to_string(curObj->getAlpha()).substr(0,3).c_str(),sizeof(alphaEntry.text));
	strncpy(rotEntry.text,to_string(curObj->getRotationDegrees()).substr(0,5).c_str(),sizeof(rotEntry.text));
	strncpy(widthLabel.text,("Width: " + to_string(curObj->w)).c_str(),sizeof(widthLabel.text));
	strncpy(heightLabel.text,("Height: " + to_string(curObj->h)).c_str(),sizeof(heightLabel.text));
}

void ItemBar::copyFields(DisplayObject * oldObj, DisplayObject * newObj){

	newObj->moveTo(oldObj->getPosition().x + 10,oldObj->getPosition().y + 10);
	newObj->setScaleX(oldObj->getScaleX()); newObj->setScaleY(oldObj->getScaleY()); 
	newObj->setRotationValue(oldObj->getRotationDegrees());
	newObj->setPivot(oldObj->getPosition());
	newObj->setAlpha(oldObj->getAlpha());
	newObj->numCopies = curObj->numCopies;
}

bool ItemBar::isEditing(){
	return idEntry.active || xPosEntry.active || yPosEntry.active || xPivEntry.active || yPivEntry.active || xScaleEntry.active || yScaleEntry.active ||
		rotEntry.active || alphaEntry.active;
} 

void ItemBar::event(SDL_Event *event, int* draw){
	//cout << "Event";
	// ID
	if(kiss_entry_event(&idEntry,event,draw)){
		if(curObj != NULL){
			curObj->setID(idEntry.text);
		}
	}

	// X Position
	if(kiss_entry_event(&xPosEntry,event,draw)){
		if(curObj != NULL){
			if(isdigit(xPosEntry.text[0]) || (isdigit(xPosEntry.text[1]) && xPosEntry.text[0] == '-')){
				int newVal = atoi(xPosEntry.text);
				curObj->moveX(newVal);
				strncpy(xPosEntry.text,to_string(newVal).c_str(),sizeof(xPosEntry.text));
			}else{
				strncpy(xPosEntry.text,to_string(curObj->getPosition().x).c_str(),sizeof(xPosEntry.text));
			}
		}
	}

	// Y Position
	if (kiss_entry_event(&yPosEntry,event,draw)){
		if(curObj != NULL){
			if(isdigit(yPosEntry.text[0]) || (isdigit(yPosEntry.text[1]) && yPosEntry.text[0] == '-')){
				int newVal = atoi(yPosEntry.text);
				curObj->moveY(newVal);
				strncpy(yPosEntry.text,to_string(newVal).c_str(),sizeof(yPosEntry.text));
			}else{
				strncpy(yPosEntry.text,to_string(curObj->getPosition().y).c_str(),sizeof(yPosEntry.text));
			}
		}
	}

	// X Pivot
	if(kiss_entry_event(&xPivEntry,event,draw)){
		if(curObj != NULL){
			if(isdigit(xPivEntry.text[0]) || (isdigit(xPivEntry.text[1]) && xPivEntry.text[0] == '-')){
				int newVal = atoi(xPivEntry.text);
				curObj->moveX(newVal);
				strncpy(xPivEntry.text,to_string(newVal).c_str(),sizeof(xPivEntry.text));
			}else{
				strncpy(xPivEntry.text,to_string(curObj->getPivot().x).c_str(),sizeof(xPivEntry.text));
			}
		}
	}

	// Y Pivot
	if (kiss_entry_event(&yPivEntry,event,draw)){
		if(curObj != NULL){
			if(isdigit(yPivEntry.text[0]) || (isdigit(yPivEntry.text[1]) && yPivEntry.text[0] == '-')){
				int newVal = atoi(yPivEntry.text);
				curObj->moveY(newVal);
				strncpy(yPivEntry.text,to_string(newVal).c_str(),sizeof(yPivEntry.text));
			}else{
				strncpy(yPivEntry.text,to_string(curObj->getPivot().y).c_str(),sizeof(yPivEntry.text));
			}
		}
	}

	// X Scale
	if(kiss_entry_event(&xScaleEntry,event,draw)){
		if(curObj != NULL){
			if(isdigit(xScaleEntry.text[0]) || isdigit(xScaleEntry.text[1]) && xScaleEntry.text[0] == '.'){
				float newVal = atof(xScaleEntry.text);
				curObj->setScaleX(newVal);
				if(scaleLocked){
					curObj->setScaleY(newVal/scale);
					strncpy(yScaleEntry.text,to_string(curObj->getScaleY()).substr(0,4).c_str(),sizeof(yScaleEntry.text));
				}
			}strncpy(xScaleEntry.text,to_string(curObj->getScaleX()).substr(0,4).c_str(),sizeof(xScaleEntry.text));
		}
	}

	// Y Scale
	if(kiss_entry_event(&yScaleEntry,event,draw)){
		if(curObj != NULL){
			if(isdigit(yScaleEntry.text[0]) || isdigit(yScaleEntry.text[1]) && yScaleEntry.text[0] == '.'){
				float newVal = atof(yScaleEntry.text);
				curObj->setScaleY(newVal);
				if(scaleLocked){
					curObj->setScaleX(scale*newVal);
					strncpy(xScaleEntry.text,to_string(curObj->getScaleX()).substr(0,4).c_str(),sizeof(xScaleEntry.text));
				}
			}
			strncpy(yScaleEntry.text,to_string(curObj->getScaleY()).substr(0,4).c_str(),sizeof(yScaleEntry.text));
		}
	}

	// Rotation
	if(kiss_entry_event(&rotEntry,event,draw)){
		if(curObj != NULL){
			if(isdigit(rotEntry.text[0]) || (isdigit(rotEntry.text[1]) && rotEntry.text[0] == '-')){
				float newVal = atof(rotEntry.text);
				curObj->setRotationValue(newVal);
			}
			strncpy(rotEntry.text,to_string(curObj->getRotationDegrees()).substr(0,5).c_str(),sizeof(rotEntry.text));
			
		}
	}

	// Alpha
	if(kiss_entry_event(&alphaEntry,event,draw)){
		if(curObj != NULL){
			if(isdigit(alphaEntry.text[0])){
				int newVal = atoi(alphaEntry.text);
				curObj->setAlpha(newVal);
			}
			strncpy(alphaEntry.text,to_string(curObj->getAlpha()).substr(0,3).c_str(),sizeof(alphaEntry.text));
			
		}
	}

	// Scale Lock Button
	if(kiss_selectbutton_event(&scaleLock,event,draw)){
		if(curObj != NULL){
				if(scaleLock.selected){
				scale = curObj->getScaleX()/curObj->getScaleY();
				scaleLocked = true;
			}else{scaleLocked = false;}
		}
	}

	// Copy Button
	if(kiss_button_event(&copyBut,event,draw)){
		if(curObj != NULL){
			DisplayObject * newObj;
			if(curObj->id.find("_cpy")){
				newObj = new DisplayObject(curObj->id.substr(0,curObj->id.find("_cpy"))+ "_cpy" + to_string(curObj->numCopies), curObj->imgPath, this->renderer);
			}else{
				newObj = new DisplayObject(curObj->id + "_cpy", curObj->imgPath, this->renderer);
			}
			curObj->numCopies++;
			((DisplayObjectContainer *)(thisWindow->getChild(SCENE_DOC_INDEX)))->addChild(newObj);
			copyFields(curObj,newObj);
			setObj(newObj);
		}
	}

	// Delete Button
	if(kiss_button_event(&delBut,event,draw)){
		if(curObj != NULL){
			((DisplayObjectContainer *)thisWindow->getChild(SCENE_DOC_INDEX))->removeImmediateChild(curObj);
			curObj = NULL;
		}
	}
}

void ItemBar::draw(SDL_Renderer *renderer){
	kiss_label_draw(&idLabel,renderer);
	kiss_label_draw(&xPosLabel,renderer);
	kiss_label_draw(&yPosLabel,renderer);
	kiss_label_draw(&xPivLabel,renderer);
	kiss_label_draw(&yPivLabel,renderer);
	kiss_label_draw(&xScaleLabel,renderer);
	kiss_label_draw(&yScaleLabel,renderer);
	kiss_label_draw(&rotLabel,renderer);
	kiss_label_draw(&widthLabel,renderer);
	kiss_label_draw(&heightLabel,renderer);
	kiss_label_draw(&alphaLabel,renderer);
	kiss_label_draw(&scaleLockLabel,renderer);

	kiss_entry_draw(&idEntry,renderer);
	kiss_entry_draw(&xPosEntry,renderer);
	kiss_entry_draw(&yPosEntry,renderer);
	kiss_entry_draw(&xPivEntry,renderer);
	kiss_entry_draw(&yPivEntry,renderer);
	kiss_entry_draw(&xScaleEntry,renderer);
	kiss_entry_draw(&yScaleEntry,renderer);
	kiss_entry_draw(&rotEntry,renderer);
	kiss_entry_draw(&alphaEntry,renderer);

	kiss_button_draw(&copyBut,renderer);
	kiss_button_draw(&delBut,renderer);
	kiss_selectbutton_draw(&scaleLock,renderer);
}