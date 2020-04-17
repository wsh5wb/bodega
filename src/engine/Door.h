#ifndef DOOR_H
#define DOOR_H

#include <vector>
#include "DisplayObject.h"
#include "AffineTransform.h"
#include <string>
#include <fstream>

using namespace std;

class Door : public DisplayObject{

public:

	Door();
	Door(string id, string filepath);
	Door(string id, string filepath, bool particle);
	Door(string id, int red, int green, int blue);
	virtual ~Door();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	virtual void saveSelf(vector<string> &objects, vector<string> &dependencies);

	bool open = true;
private:


};

#endif
