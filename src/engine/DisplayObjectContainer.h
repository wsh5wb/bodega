#ifndef DISPLAYOBJECTCONTAINER_H
#define DISPLAYOBJECTCONTAINER_H

#include <vector>
#include "DisplayObject.h"
#include "AffineTransform.h"
//#include "Event.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class DisplayObjectContainer : public DisplayObject{

public:
	
	DisplayObjectContainer();
	DisplayObjectContainer(string id, string filepath);
	DisplayObjectContainer(string id, string filepath, SDL_Renderer* renderer);
	DisplayObjectContainer(string id, int red, int green, int blue);
	DisplayObjectContainer(string id, int red, int green, int blue, SDL_Renderer* renderer);
	virtual ~DisplayObjectContainer();

	void addChild(DisplayObject* child);
	void removeImmediateChild(DisplayObject* child);
	void removeImmediateChild(string id);
	void removeChild(int index);
	void removeThis();
	
	virtual int numChildren();
	virtual DisplayObject* getChild(int index);
	virtual DisplayObject* getChild(string id);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	virtual void saveSelf(vector<string> &objects, vector<string> &dependencies);

	vector<DisplayObject*> children;
private:
	
	
};

#endif