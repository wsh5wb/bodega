#include "TweenParam.h"

TweenParam::TweenParam(int paramToTween, double startVal, double endVal,
		double time, int transition) {
	this->param = paramToTween;
	this->startVal = startVal;
	this->endVal = endVal;
	this->tweenTime = time;
	this->transition = transition;
}

int TweenParam::getParam() {
	return param;
}

double TweenParam::update(double currentValue){
	return 0.0;
}

double TweenParam::getStartVal() {
	return startVal;
}

double TweenParam::getEndVal() {
	return endVal;
}

double TweenParam::getTweenTime() {
	return tweenTime;
}

double TweenParam::percentComplete(){
	return (frameCount/tweenTime);
}

double TweenParam::linearTransform(int dir) {
	return (1.0/tweenTime)*(endVal - startVal);
}

double TweenParam::quadraticTransform(int dir) {
	double in = percentComplete();
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
	return 0;
}
