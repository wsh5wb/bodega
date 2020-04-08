#ifndef TWEEN_H
#define TWEEN_H

#include "TweenParam.h"
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include <cmath>

class Tween{

public:
	Tween(DisplayObject* object);
	//Tween(DisplayObject* object, TweenTransitions transition); //this is covered by the flags
	void animate(int fieldToAnimate, double startVal, double endVal, double time, int transition, int direction);
	void update(); //invoked once per frame by the TweenJuggler. Updates this tween / DisplayObject
	bool isComplete();
	void setValue(int param, double value);
	double currentParamValue(int param);


private:

	DisplayObject* object;
	vector<TweenParam*> tweenParams;
};


#endif
