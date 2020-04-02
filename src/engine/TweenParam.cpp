#include "TweenParam.h"

TweenParam::TweenParam(int paramToTween, double startVal, double endVal,
		double time, int flags) {
	this->param = paramToTween;
	this->startVal = startVal;
	this->endVal = endVal;
	this->tweenTime = time;
	this->flags = flags;
}

int TweenParam::getParam() {
	return param;
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

int TweenParam::getFlags() {
	return flags;
}
