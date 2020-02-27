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

ResourceBar::ResourceBar(int windowWidth, int windowHeight, DisplayObject *draggable) : DisplayObjectContainer(){
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->drag = draggable;
	this->id = "resourcebar";
	cout << windowWidth << windowHeight << endl;
	menu = new DisplayObjectContainer();
	int base_height = (int) (windowHeight * (4.0/7.0));
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
	
	if(this->mouseListener->leftClick){
		cout << "making new obj" << endl;
		for(DisplayObject* child : menu->children){
			cout << "checking " << child->id << endl;
			auto child_coords = child->getPosition();
			auto click_coords = this->mouseListener->getPosition();
			if (dist(child_coords, click_coords) < 30){
				this->drag = new DisplayObject(child->id, child->imgPath);
				auto point = this->mouseListener->getPosition();
				this->drag->moveTo(point.x, point.y);
				break;
			}
		}
	}

	SDL_Event sdlevent;
    sdlevent.type = SDL_KEYDOWN;
    sdlevent.key.keysym.sym = SDLK_1;

 	SDL_PushEvent(&sdlevent);
}