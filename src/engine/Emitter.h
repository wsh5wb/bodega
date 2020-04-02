#ifndef EMITTER_H
#define EMITTER_H

#include "Sprite.h"
#include "Particle.h"

using namespace std;

class Emitter : public Sprite{
public:
	Emitter();
	Emitter(int w, int h, bool play);
	Emitter(string id, string filepath, bool play);
	~Emitter();

	void addParticle(string path, int speedX, int speedY, int timeout, int generateTime, double scaleX, double scaleY);
	void addRandParticle(string path, int xLow, int xHigh, int yLow, int yHigh, int timeout, int generateTime, double scaleX, double scaleY);
	void start();
	void stop();

	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

private:
	vector<Particle*> particleType;
	vector<Particle*> particles;
	bool playing;
};

#endif