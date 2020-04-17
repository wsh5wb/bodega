#ifndef OBJECT_H
#define OBJECT_H

#include "DisplayObject.h"
#include "AffineTransform.h"
#include <string>
#include <fstream>

using namespace std;

class Object : public DisplayObject{

public:

	Object();

	virtual ~Object();

	void hitbox();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	virtual void saveSelf(vector<string> &objects, vector<string> &dependencies);

	double boundLowX, boundHighX, boundLowY, boundHighY;

private:


};

#endif
