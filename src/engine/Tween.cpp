#include "Tween.h"
#include <iostream>

using namespace std;

Tween::Tween(DisplayObject *obj) {
	object = obj;
}
//Tween(DisplayObject* object, TweenTransitions transition); //this is covered by the flags

void Tween::animate(int fieldToAnimate, double startVal, double endVal,
		double timetoComplete,int transition, int direction) {
	tweenParams.push_back(
			new TweenParam(fieldToAnimate, startVal, endVal, timetoComplete, transition, direction));
}
//invoked once per frame by the TweenJuggler. Updates this tween / DisplayObject
void Tween::update() {
	//printf(" Size of TweenParams %x, \n", tweenParams.size());
	for (vector<TweenParam*>::iterator it = tweenParams.begin(); it != tweenParams.end(); ) {
		TweenParam *t = *it;

		double currentValue = currentParamValue(t->getParam());
		if(t->getEndVal() != currentValue){
			currentValue = t->update(currentValue);
			setValue(t->getParam(), currentValue);
			it++;
		}else{
			it = tweenParams.erase(it);
		}

	}
}

bool Tween::isComplete() {
	//not correct, is complete should only complete once every field associated with this particular Tween has finished.
	bool completed = true;
	for (TweenParam *t : tweenParams) {
		if(t->getEndVal() != currentParamValue(t->getParam()) && t->getFrameCount() < t->getTweenTime()){
				completed = false;
				//printf("The Value of %x is %f \n", t->getParam(), currentParamValue(t->getParam()));
				//printf("Not Completed.");
			}
	}
	return completed;
}

void Tween::setValue(int param, double value) {
	// alters the value of a particular param to a new value. If it's within a certain margin of the endVal, set to the endVal
	switch (param) {

	case TWEEN_POSITION_X: {
		SDL_Point p = object->getPosition();
		p.x = value;
		object->setPosition(p);
		break;
	}
	case TWEEN_POSITION_Y: {
		SDL_Point p = object->getPosition();
		p.y = value;
		object->setPosition(p);
		break;
	}
	case TWEEN_PIVOT_X:{
		SDL_Point p = object->getPivot();
		p.x = value;
		object->setPivot(p);
		break;
	}
	case TWEEN_PIVOT_Y:{
		SDL_Point p = object->getPivot();
		p.y = value;
		object->setPivot(p);
		break;
	}
	case TWEEN_SCALE_X: {
		object->setScaleX(value);
		break;
	}
	case TWEEN_SCALE_Y: {
		object->setScaleY(value);
		break;
	}
	case TWEEN_ROTATION: {
		object->setRotation(value);
		break;
	}
	case TWEEN_ALPHA: {
		object->setAlpha(int(value));
		break;
	}
	default: {
		printf("Error reached with %x \n", param);
		cerr << "ERROR: Tween Parameter Not Recognized!\n";
		break;
	}

}
}

double Tween::currentParamValue(int param){
	double start = 0;
	switch (param) {

	case TWEEN_POSITION_X: {
		SDL_Point p = object->getPosition();
		start = p.x;
		break;
	}
	case TWEEN_POSITION_Y: {
		SDL_Point p = object->getPosition();
		start = p.y;
		break;
	}
	case TWEEN_PIVOT_X:{
		SDL_Point p = object->getPivot();
		start = p.x;
		break;
	}
	case TWEEN_PIVOT_Y:{
		SDL_Point p = object->getPivot();
		start = p.y;
		break;
	}
	case TWEEN_SCALE_X: {
		start = object->getScaleX();
		break;
	}
	case TWEEN_SCALE_Y: {
		start = object->getScaleY();
		break;
	}
	case TWEEN_ROTATION: {
		start = object->getRotation();
		break;
	}
	case TWEEN_ALPHA: {
		start = double(object->getAlpha());
		break;
	}
	default: {
		printf("Error reached with %x \n", param);
		cerr << "ERROR: Tween Parameter Not Recognized!\n";
		break;
	}
	}
	return start;
}
