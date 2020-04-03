#include "Tween.h"
#include <iostream>

using namespace std;

Tween::Tween(DisplayObject *obj) {
	object = obj;
}

//Tween(DisplayObject* object, TweenTransitions transition); //this is covered by the flags

void Tween::animate(int fieldToAnimate, double startVal, double endVal,
		double timetoComplete,int transition) {
	tweenParams.push_back(
			new TweenParam(fieldToAnimate, startVal, endVal, timetoComplete, transition));
}
//invoked once per frame by the TweenJuggler. Updates this tween / DisplayObject
void Tween::update() {
	for (TweenParam *t : tweenParams) {
		double currentValue = currentParamValue(t->getParam());
		//double percentIn = abs((t->getEndVal() - currentValue)/ (t->getEndVal() - t->getStartVal()));
		if(t->getEndVal() != currentValue){
			currentValue = t->update(currentValue);
			setValue(t->getParam(), currentValue);
		}
	}
}

bool Tween::isComplete() {
	//not correct, is complete should only complete once every field associated with this particular Tween has finished.
	bool completed = true;
	for(vector <TweenParam *> :: iterator it = this->tweenParams.begin(); it != this->tweenParams.end(); ++it){
			if((*it)->getEndVal() != currentParamValue((*it)->getParam())){
				completed = false;
			}
	}
	return completed;
}

void Tween::setValue(int param, double value) {
	// alters the value of a particular param to a new value. If it's within a certain margin of the endVal, set to the endVal

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
		start = object->getAlpha();
		break;
	}
	default: {
		cerr << "ERROR: Tween Parameter Not Recognized!\n";
		return start;
	}
	}
	return start;
}

double Tween::linearTransform(double in, int dir) {
	return in;
}

double Tween::quadraticTransform(double in, int dir) {
	switch (dir) {
	case TWEEN_IN: {
		return in * in;
	}
	case TWEEN_OUT: {
		double inv = 1-in;
		return 1 - (inv*inv);
	}
	case TWEEN_INOUT: {
			return in<=.5?(2*in*in):.5+(1-(1.5-in)*(1.5-in));
		}
	case TWEEN_OUTIN: {
			return in<=.5?(2*in*in):.5+(1-(1.5-in)*(1.5-in));//needs to be finished
		}
	}
}
