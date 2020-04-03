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
	this->tweens.push_back(tween);
}

void TweenJuggler::nextFrame() {
	//TODO: do the things and clear the done things
	for(vector <Tween*> :: iterator it = this->tweens.end(); it != this->tweens.begin(); --it){
			if ((*it)->isComplete()){
				this->tweens.erase(it);
			}else{
				(*it)->update();
			}
	}
}
