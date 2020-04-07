#ifndef TWEEN_PARAM_H
#define TWEEN_PARAM_H

#include "TweenDefs.h"
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"

class TweenParam {

public:
	TweenParam(int paramToTween, double startVal, double endVal,
			double time, int flags);
	int getParam();
	double getStartVal();
	double getEndVal();
	double getTweenTime();
	int getFlags();

private:

	int param = -1;
	double startVal = -1;
	double endVal = -1;
	double tweenTime = -1;
	int flags = 0;

};

#endif
