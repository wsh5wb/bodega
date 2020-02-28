#ifndef ITEMBAR_H
#define ITEMBAR_H

#include "kiss_sdl.h"
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class ItemBar {
public:
	ItemBar();
	ItemBar(kiss_window * wdw);
	~ItemBar();
	void setObj(DisplayObject *& obj);
	void initThisWindow(DisplayObjectContainer * win);
	void updateObjectFields();
	void copyFields(DisplayObject * oldObj, DisplayObject * newObj);
	//bool isEditing();
	void event(SDL_Event *event, int* draw);
	void draw(SDL_Renderer *renderer);
	kiss_window * window = {0};
private:
	DisplayObjectContainer * thisWindow;

	DisplayObject * curObj;
	kiss_entry idEntry = {0}; kiss_entry xPosEntry = {0}; kiss_entry yPosEntry = {0}; kiss_entry xPivEntry = {0}; kiss_entry yPivEntry = {0}; 
	kiss_entry xScaleEntry = {0}; kiss_entry yScaleEntry = {0}; kiss_entry rotEntry = {0}; kiss_entry alphaEntry = {0};

	kiss_label idLabel = {0}; kiss_label xPosLabel = {0}; kiss_label yPosLabel = {0}; kiss_label xPivLabel = {0}; kiss_label yPivLabel = {0}; 
	kiss_label xScaleLabel = {0}; kiss_label yScaleLabel = {0}; kiss_label rotLabel = {0}; kiss_label widthLabel = {0}; kiss_label heightLabel = {0};
	kiss_label alphaLabel = {0};

	kiss_button delBut = {0}; kiss_button copyBut = {0};

};

#endif