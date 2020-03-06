#include "Animations.h"

Animation::Animation(){

}

Animation::Animation(string basepath, int startIndex, int numFrames, int frameRate,bool loop){
	this->basepath = basepath;
	this->numFrames = numFrames;
	this->startIndex = startIndex;
	this->endIndex = startIndex + numFrames-1;
	this->frameRate = frameRate;
	this->loop = loop;
	usesSheet = false;
}

Animation::Animation(string sheetpath, string xmlpath, int startIndex, int frameRate, bool loop){
	basepath = sheetpath;
	this->xmlpath = xmlpath;
	this->loop = loop;
	usesSheet = true;
	this->startIndex = startIndex;

	this->frameRate = frameRate;
	this->loop = loop;
}