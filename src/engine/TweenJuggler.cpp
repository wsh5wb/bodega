#include "TweenJuggler.h"

TweenJuggler *TweenJuggler::instance = 0;

TweenJuggler::TweenJuggler() {

}
TweenJuggler::~TweenJuggler() {
	delete instance;
}

TweenJuggler* TweenJuggler::getInstance() {
	if (instance == 0) {
		instance = new TweenJuggler();
	}
	return instance;
}

void TweenJuggler::add(Tween* tween) {
	this->tweens.push_back(tween);
}

void TweenJuggler::nextFrame() {
	//TODO: do the things and clear the done things
	//printf("Going to next frame \n");
	auto it = tweens.begin();
	while (it != tweens.end()){
			if ((*it)->isComplete()){
				printf("Completed \n");
				this->tweens.erase(it);
			}else{
				(*it)->update();
				++it;
			}
	}
}
