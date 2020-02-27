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

ResourceBar::ResourceBar(int windowWidth, int windowHeight, DisplayObject *draggable, DisplayObjectContainer *mainwindow) : DisplayObjectContainer(){
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->drag = draggable;
	this->mainWindow = mainwindow;
	cout << windowWidth << windowHeight << endl;
	menu = new DisplayObjectContainer();
	int base_height = (int) (windowHeight * (3.0/4.0));
	cout << base_height << std::endl;
	int x = 0;
	int y = 0;
	menu->moveTo(0, base_height);
	
	for (const auto& dirEntry : std::filesystem::recursive_directory_iterator("./resources")){
		std::filesystem::path path = dirEntry.path();
		string string_path = path.string();
		std::error_code ec;
		if (std::filesystem::is_regular_file(path, ec) and checkExt(string_path)){
			std::cout << path << std::endl;
			DisplayObject* temp = new DisplayObject(string_path, string_path);
			temp->scale(.1);
			temp->moveTo(x,y);
			x += 30;
			if(x > windowWidth* 3){
			 	y += 40;
			 	x = 0;
			}
	    	menu->addChild(temp);
	    	//std::cout << dirEntry << std::endl;
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
	DisplayObjectContainer::draw(at);
	menu->draw(at);
	if(drag != NULL)
		drag->draw(at);
}

void ResourceBar::update(set<SDL_Scancode> pressedKeys){
	DisplayObjectContainer::update(pressedKeys);

	// keyboard actions
	for(SDL_Scancode code : pressedKeys){
		switch(code){

			case SDL_SCANCODE_DOWN:
			{
				menu->translateDown();
				break;
			}case SDL_SCANCODE_UP:
			{
				menu->translateUp();
				break;
			}case SDL_SCANCODE_LEFT:
			{
				menu->translateLeft();
				break;
			}case SDL_SCANCODE_RIGHT:
			{
				menu->translateRight();
				break;
			}
		}
	}
	
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
		cout << "click" << endl;
		for(DisplayObject* child : menu->children){
			auto child_coords = child->getWorld();
			auto click_coords = this->mouseListener->getCoordinates();
			//cout << "child x: " << child_coords.x << " child y: " << child_coords.y << endl;
			if (dist(child_coords, click_coords) < 30){
				cout << "making new obj" << endl;
				cout << "checking " << child->id << " " << dist(child_coords, click_coords) <<  endl;
				this->drag = new DisplayObject(child->id, child->imgPath);
				break;
			}
		}
	}
	else if (drag != NULL){
		mainWindow->addChild(drag);
		drag = NULL;
	}

	SDL_Event sdlevent;
    sdlevent.type = SDL_KEYDOWN;
    sdlevent.key.keysym.sym = SDLK_1;

 	SDL_PushEvent(&sdlevent);
}