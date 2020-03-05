#ifndef TWEENJUGGLER_H
#define TWEENJUGGLER_H

#include "Tween.h"
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"

class TweenJuggler{

public:
	TweenJuggler();
	~TweenJuggler();

	static TweenJuggler* getInstance();
	void add(Tween* tween);
	void nextFrame();


private:

	static TweenJuggler* instance;
	vector<Tween*> tweens;

};


#endif
