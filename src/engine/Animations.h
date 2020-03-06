#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <string>

using namespace std;
class Animation{
public:
	Animation();
	Animation(string basepath, int startIndex, int numFrames, int frameRate,bool loop);
	Animation(string sheetpath, string xmlpath, int startIndex, int frameRate, bool loop);
	string basepath, xmlpath;
	bool loop, usesSheet;
	int numFrames, frameRate, startIndex, endIndex;
private:

};

#endif