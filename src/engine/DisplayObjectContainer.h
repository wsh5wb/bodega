#ifndef DISPLAYOBJECTCONTAINER_H
#define DISPLAYOBJECTCONTAINER_H

#include <vector>
#include "DisplayObject.h"
#include "AffineTransform.h"
#include <string>
#include <fstream>
																					
using namespace std;

class DisplayObjectContainer : public DisplayObject{

public:
	
	DisplayObjectContainer();
	DisplayObjectContainer(string id, string filepath);
	DisplayObjectContainer(string id, string filepath, bool particle);
	DisplayObjectContainer(string id, int red, int green, int blue);
	virtual ~DisplayObjectContainer();

	void addChild(DisplayObject* child);
	void removeImmediateChild(DisplayObject* child);
	void removeImmediateChild(string id);
	void removeImmediateChildNoDelete(DisplayObject* child);
	void removeImmediateChildNow(DisplayObject* child);
	void removeChild(int index);
	void removeThis();

	void addToCollisionSystem();
	void removeFromCollisionSystem();

	virtual void resetDelta();
	
	virtual int numChildren();
	virtual DisplayObject* getChild(int index);
	virtual DisplayObject* getChild(string id);

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	virtual void saveSelf(vector<string> &objects, vector<string> &dependencies);
	virtual void cleanUpDisplayTree();


	vector<DisplayObject*> children;
private:
	
	
};

#endif
