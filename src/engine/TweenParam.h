#ifndef TWEEN_PARAM_H
#define TWEEN_PARAM_H

#include "TweenDefs.h"
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"

class TweenParam {

public:
	TweenParam(int paramToTween, double startVal, double endVal,
			double time, int transition);
	int getParam();
	double update(double currentValue);
	double getStartVal();
	double getEndVal();
	double getTweenTime();
	double linearTransform(int dir);
	double quadraticTransform(int dir);
	double percentComplete();
private:

	int param = 0;
	int frameCount = 0;
	double startVal = -1;
	double endVal = -1;
	double tweenTime = -1;
	int transition = 0;

};

#endif
