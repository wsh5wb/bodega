#include "TweenJuggler.h"

TweenJuggler *TweenJuggler::instance = 0;

TweenJuggler::TweenJuggler() {

}
TweenJuggler::~TweenJuggler() {

}

TweenJuggler* TweenJuggler::getInstance() {
	if (instance == 0) {
		instance = new TweenJuggler();
	}
	return instance;
}

void TweenJuggler::add(Tween* tween) {
	tweens->push_back(tween);
}

void TweenJuggler::nextFrame() {
	//TODO: do the things and clear the done things
}


