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
