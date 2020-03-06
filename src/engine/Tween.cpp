#include "Tween.h"
#include <iostream>

using namespace std;

Tween::Tween(DisplayObject *obj) {
	object = obj;
}

//Tween(DisplayObject* object, TweenTransitions transition); //this is covered by the flags

void Tween::animate(int fieldToAnimate, double startVal, double endVal,
		double time, int flags) {
	tweenParams.push_back(
			new TweenParam(fieldToAnimate, startVal, endVal, time, flags));
}

//invoked once per frame by the TweenJuggler. Updates this tween / DisplayObject
void Tween::update() {
	//TODO: this
	for (TweenParam *t : tweenParams) {
		int flag = t->getFlags();
		int function = flag & (~3);
		int direction = flag & 3;
		double percentIn = 0; //need some way to calculate this, might need to store start time or something similar
		switch (function) {
		case TWEEN_LINEAR: {
			double amnt = linearTransform(percentIn, direction);
			double newVal;
		}
		}
	}
}

void Tween::isComplete() {
	//TODO: i think this just does something with an event
}

void Tween::setValue(int param, double value, int flags) {
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
		return;
	}
	}
	TweenParam *temp = new TweenParam(param, start, value, 60, flags);
	tweenParams.push_back(temp);
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
