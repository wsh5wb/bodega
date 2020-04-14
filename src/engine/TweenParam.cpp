#include "TweenParam.h"

TweenParam::TweenParam(int paramToTween, double startVal, double endVal,
		double time, int transition, int direction) {
	this->param = paramToTween;
	this->startVal = startVal;
	this->endVal = endVal;
	this->tweenTime = time;
	this->transition = transition;
	this->direction = direction;
}

int TweenParam::getParam() {
	return param;
}

int TweenParam::getDir(){
	return direction;
}

double TweenParam::getFrameCount(){
	return frameCount;
}

double TweenParam::update(double currentValue){
	frameCount += 1;
	if(frameCount >= tweenTime){
		return endVal;
	}
	else{
		switch (transition) {
			case TWEEN_LINEAR:{
				return linearTransform(direction);
			}
			case TWEEN_QUADRATIC:{
				return quadraticTransform(direction);
			}
			case TWEEN_SINE:{
				return sineTransform(direction);
			}
			case TWEEN_CUBIC:{
				return cubicTransform(direction);
			}
			case TWEEN_QUARTIC:{
				return quartTransform(direction);
			}
			case TWEEN_QUINTIC:{
				return quintTransform(direction);
			}
			case TWEEN_BACK:{
				return backTransform(direction);
			}
			case TWEEN_ELASTIC:{
				return elasticTransform(direction);
			}
		}
	}
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

//@t is the current time (or position) of the tween. This can be seconds or frames, steps, seconds, ms, whatever – as long as the unit is the same as is used for the total time [3].
//@b is the beginning value of the property.
//c is the change between the beginning and destination value of the property.
//@d is the total time of the tween.
// 	return c*t/d + b;

double TweenParam::linearTransform(int dir) {
			return (endVal - startVal) * frameCount/tweenTime + startVal;
}

double TweenParam::quadraticTransform(int dir) {
	double c = (endVal - startVal);
	double t = frameCount;
	double d = tweenTime;
	double b = startVal;
	switch (dir) {
	case EASE_IN: {
			return c*(t/=d)*t + b;
	}
	case EASE_OUT: {
			return -c *(t/=d)*(t-2) + b;
		}
	case EASE_INOUT: {
		if ((t/=d/2) < 1) return ((c/2)*(t*t)) + b;
		return -c/2 * (((t-2)*(--t)) - 1) + b;
		}
	}
	return 0;
}

double TweenParam::sineTransform(int dir) {
	double c = (endVal - startVal);
	double t = frameCount;
	double d = tweenTime;
	double b = startVal;
	switch (dir) {
	case EASE_IN: {
			return -c * cos(t/d * (PI/2)) + c + b;
	}
	case EASE_OUT: {
			return c * sin(t/d * (PI/2)) + b;
	}
	case EASE_INOUT: {
			return -c/2 * (cos(PI*t/d) - 1) + b;
	}
}
return 0;

}

double TweenParam::quintTransform(int dir) {
	double c = (endVal - startVal);
	double t = frameCount;
	double d = tweenTime;
	double b = startVal;
	switch (dir) {
	case EASE_IN: {
		return c*(t/=d)*t*t*t*t + b;
	}
	case EASE_OUT: {
		return c*((t=t/d-1)*t*t*t*t + 1) + b;
	}
	case EASE_INOUT: {
		if ((t/=d/2) < 1) return c/2*t*t*t*t*t + b;
		return c/2*((t-=2)*t*t*t*t + 2) + b;
	}
}
	return 0;
}

double TweenParam::quartTransform(int dir) {
	double c = (endVal - startVal);
	double t = frameCount;
	double d = tweenTime;
	double b = startVal;
	switch (dir) {
	case EASE_IN: {
		return c*(t/=d)*t*t*t + b;
	}
	case EASE_OUT: {
		return -c * ((t=t/d-1)*t*t*t - 1) + b;
	}
	case EASE_INOUT: {
		if ((t/=d/2) < 1) return c/2*t*t*t*t + b;
		return -c/2 * ((t-=2)*t*t*t - 2) + b;
	}
}
	return 0;
}

double TweenParam::expoTransform(int dir) {
	double c = (endVal - startVal);
	double t = frameCount;
	double d = tweenTime;
	double b = startVal;
	switch (dir) {
	case EASE_IN: {
			return (t==0) ? b : c * pow(2, 10 * (t/d - 1)) + b;
	}
	case EASE_OUT: {
			return (t==d) ? b+c : c * (-pow(2, -10 * t/d) + 1) + b;
	}
	case EASE_INOUT: {
		if (t==0) return b;
		if (t==d) return b+c;
		if ((t/=d/2) < 1) return c/2 * pow(2, 10 * (t - 1)) + b;
		return c/2 * (-pow(2, -10 * --t) + 2) + b;
	}
}
	return 0;
}

double TweenParam::elasticTransform(int dir) {
	double c = (endVal - startVal);
	double t = frameCount;
	double d = tweenTime;
	double b = startVal;
	switch (dir) {
	case EASE_IN: {
		if (t==0) return b;  if ((t/=d)==1) return b+c;
		float p=d*.3f;
		float a=c;
		float s=p/4;
		float postFix =a*pow(2,10*(t-=1));
		return -(postFix * sin((t*d-s)*(2*PI)/p )) + b;
	}
	case EASE_OUT: {
		if (t==0) return b;  if ((t/=d)==1) return b+c;
		float p=d*.3f;
		float a=c;
		float s=p/4;
		return (a*pow(2,-10*t) * sin( (t*d-s)*(2*PI)/p ) + c + b);
	}
	case EASE_INOUT: {
		if (t==0) return b;  if ((t/=d/2)==2) return b+c;
		float p=d*(.3f*1.5f);
		float a=c;
		float s=p/4;

		if (t < 1) {
			float postFix =a*pow(2,10*(t-=1));
			return -.5f*(postFix* sin( (t*d-s)*(2*PI)/p )) + b;
		}
		float postFix =  a*pow(2,-10*(t-=1));
		return postFix * sin( (t*d-s)*(2*PI)/p )*.5f + c + b;
	}
}
	return 0;
}

double TweenParam::cubicTransform(int dir) {
	double c = (endVal - startVal);
	double t = frameCount;
	double d = tweenTime;
	double b = startVal;
	switch (dir) {
	case EASE_IN: {
		return c*(t/=d)*t*t + b;
	}
	case EASE_OUT: {
		return c*((t=t/d-1)*t*t + 1) + b;
		}
	case EASE_INOUT: {
		if ((t/=d/2) < 1) return c/2*t*t*t + b;
		return c/2*((t-=2)*t*t + 2) + b;
		}
	}
	return 0;
}

double TweenParam::backTransform(int dir) {
	double c = (endVal - startVal);
	double t = frameCount;
	double d = tweenTime;
	double b = startVal;
	switch (dir) {
	case EASE_IN: {
		float s = 1.70158f;
		float postFix = t/=d;
		return c*(postFix)*t*((s+1)*t - s) + b;
	}
	case EASE_OUT: {
		float s = 1.70158f;
		return c*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
		}
	case EASE_INOUT: {
		float s = 1.70158f;
			if ((t/=d/2) < 1) return c/2*(t*t*(((s*=(1.525f))+1)*t - s)) + b;
			float postFix = t-=2;
			return c/2*((postFix)*t*(((s*=(1.525f))+1)*t + s) + 2) + b;
		}
	}
	return 0;
}
