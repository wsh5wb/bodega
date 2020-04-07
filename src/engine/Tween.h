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
	void animate(int fieldToAnimate, double startVal, double endVal, double time, int flags);
	void update(); //invoked once per frame by the TweenJuggler. Updates this tween / DisplayObject
	void isComplete();
	void setValue(int param, double value, int flags);


private:

	DisplayObject* object;
	vector<TweenParam*> tweenParams;

	double linearTransform(double in, int dir);
	double quadraticTransform(double in, int dir);
	double sineTransform(double in, int dir);

};


#endif
