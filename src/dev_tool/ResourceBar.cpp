#include "ResourceBar.h"

bool checkExt(const string& filename)
{
    size_t pos = filename.rfind('.');
    if (pos == string::npos)
        return false;

    string ext = filename.substr(pos+1);

    if (ext == "jpg" || ext == "jpeg" || ext == "gif" || ext == "png")
        return true;

    return false;
}

ResourceBar::ResourceBar(int windowWidth, int windowHeight, DisplayObject *draggable, DisplayObjectContainer *mainwindow, ItemBar * bar) : DisplayObjectContainer(){
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->drag = draggable;

	this->mainWindow = mainwindow;
	this->baseHeight = (int) (windowHeight * (3.0/4.0));
	this->infoBar = bar;

	menu = new DisplayObjectContainer();
	//cout << baseHeight << std::endl;
	int x = 0;
	int y = 0;
	count = 0;
	menu->moveTo(0, baseHeight);
	
	for (const auto& dirEntry : std::filesystem::recursive_directory_iterator("./resources")){
		std::filesystem::path path = dirEntry.path();
		string string_path = path.string();
		std::error_code ec;

		if (std::filesystem::is_regular_file(path, ec) and checkExt(string_path)){
			std::cout << path << std::endl;

			DisplayObject* temp = new DisplayObject("Default", string_path);
			//scale to fixed pixel width  1/15 of total display width 
			double scaleFactor = (windowWidth/25.0) / temp->w;
			temp->scale(scaleFactor);
			temp->moveTo(x,y);
			x += temp->w*scaleFactor + 2.;
			if(x > windowWidth* 2.75){
			 	y += temp->h*scaleFactor + 2.;
			 	x = 0;
			}
	    	menu->addChild(temp);
		}

	}
}

ResourceBar::~ResourceBar(){
	delete menu;
}

void ResourceBar::addChild(DisplayObject* obj){
	DisplayObjectContainer::addChild(obj);
}

void ResourceBar::setMouseListener(Mouse* mouse){
	this->mouseListener = mouse;
}

void ResourceBar::draw(AffineTransform &at){
	if(!vis){return;}
	menu->draw(at);
	if(drag != NULL)
		drag->draw(at);
}

void ResourceBar::update(set<SDL_Scancode> pressedKeys){
	DisplayObjectContainer::update(pressedKeys);

	// keyboard actions
	for(SDL_Scancode code : pressedKeys){
		switch(code){
			case SDL_SCANCODE_H:
			{
				//cout << "Do stuff" << menu->vis<< endl;
				this->toggleVisibility();
				SDL_Delay(150);
				break;
			}
		}
	}
	if(!vis){return;}

	if(this->mouseListener == NULL)	return;

	// mouse actions
	if(this->mouseListener->isScrolling){
		if (this->mouseListener->wheelUp){
			SDL_Point pos = menu->getPosition();
			if(pos.x < -windowWidth* 2)
				pos.x = -windowWidth* 2;

			menu->moveTo(pos.x-20,pos.y);
			//menu->translateLeft();
		}
		else if(this->mouseListener->wheelDown){
			SDL_Point pos = menu->getPosition();
			if(pos.x > 0)
				pos.x = 0;
			menu->moveTo(pos.x+20,pos.y);
			//menu->translateRight();
		}
	}
	
	if (drag != NULL and this->mouseListener->leftClick){
		auto point = this->mouseListener->getCoordinates();
		drag->moveTo(point.x, point.y);
	}
	else if(this->mouseListener->leftClick){ //handle resourcebar left clicks
		// cout << "click" << endl;
		auto click_coords = this->mouseListener->getCoordinates();
		if (click_coords.y < baseHeight){

		} // if the click is outside of the resourcebar
		else{
			for(DisplayObject* child : menu->children){
				auto child_coords = child->getWorldCenter();
				//cout << "child x: " << child_coords.x << " child y: " << child_coords.y << endl;
				if (dist(child_coords, click_coords) < 30){
					// cout << "checking " << child->id << " " << dist(child_coords, click_coords) <<  endl;
					this->drag = new DisplayObject(child->id + to_string(count), child->imgPath);
					count++;
					this->drag->isCopy = true;
					break;
				}
			}
		}
	}
	else if (drag != NULL and drag->isCopy){
		drag->isCopy = false;
		((DisplayObjectContainer*) mainWindow->children[SCENE_DOC_INDEX])->addChild(drag);
		infoBar->setObj(drag);
		drag = NULL;
	}

	SDL_Event sdlevent;
    sdlevent.type = SDL_KEYDOWN;
    sdlevent.key.keysym.sym = SDLK_1;

 	SDL_PushEvent(&sdlevent);
}
