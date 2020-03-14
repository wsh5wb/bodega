#include "AnimatedSprite.h"
#include <fstream>

AnimatedSprite::AnimatedSprite(){

}

AnimatedSprite::AnimatedSprite(string id){
	this->id = id;
}

AnimatedSprite::AnimatedSprite(string id, string filepath){
	SDL_Surface* image = IMG_Load(filepath.c_str());
	images.push_back(image);
	this->id = id;
	loop = false;
	curFrame = 0;
	DisplayObject::setImage(image);
}

// AnimatedSprite::AnimatedSprite(string id, string sheetpath, string xmlpath){
// 	this.id = id;
// 	usesSheet = true;
// }

AnimatedSprite::~AnimatedSprite(){
	int i = 0;
	for(vector<SDL_Surface*>::iterator it = images.begin(); it != images.end(); it++){
		if(i == curFrame && !usesSheet){
			continue;
		}if(usesSheet && i == startIndex){continue;}
		i++;
		SDL_FreeSurface(*it);
	}images.clear();
	for(unordered_map<string,Animation*>::iterator it2 = animationMap.begin(); it2 != animationMap.end();it2++){
		delete it2->second;
	}
}

void AnimatedSprite::addAnimation(string basepath, string animName, int numFrames, int frameRate, bool loop){
	Animation * a = new Animation(basepath,images.size(),numFrames,frameRate,loop);
	animationMap.emplace(animName,a);

	for(int i=1; i<numFrames+1;i++){
		SDL_Surface* image = IMG_Load((basepath + "_" + to_string(i) + ".png").c_str());
		images.push_back(image);
		cout << basepath + "_" + to_string(i) + ".png" << endl;
	}
}

void AnimatedSprite::addAnimation(string sheetpath, string xmlpath, string animName, int numFrames, int frameRate, bool loop){
	ifstream in(xmlpath);
	if(!in){
		cout << "XML File not found";
		return;
	}

	Animation * a = new Animation(sheetpath,xmlpath,images.size(),frameRate,loop);
	animationMap.emplace(animName,a);

	SDL_Surface* image = IMG_Load((sheetpath).c_str());
	images.push_back(image);

}

Animation* AnimatedSprite::getAnimation(string animName){
	if(animationMap.find(animName) == animationMap.end()){
		cout << "Animation not in map";
		return NULL;
	}
	return animationMap[animName];
}

void AnimatedSprite::play(string animName){
	
	Animation* a = getAnimation(animName);

	usesSheet = a->usesSheet;
	loop = a->loop;
	startIndex = a->startIndex;
	frameRate = a->frameRate;

	if(usesSheet){
		string buffer; 
		char c;
		ifstream in(a->xmlpath);
		if(!in){
			cout << "XML File not found";
			return;
		}while(in.get(c)){
			buffer += c;
		}in.close();
		vector<string> positions;
		unsigned int pos = 0;
		unsigned int start;
		while(true){
			start = buffer.find ("<TextureAtlas",pos);
			if(start == string::npos) {break;}
			start = buffer.find(">",start);
			start++;
			pos = buffer.find("</TextureAtlas",start);
			if(pos == string::npos) {break;}
			buffer = buffer.substr(start,pos-start);
			break;
		}
		pos = 0, start =0;
		while(buffer.find("<",start) != string::npos){
			start = buffer.find("<",start);
			if(start == string::npos){break;}
			pos = buffer.find(">",start);
			if(pos == string::npos){break;}
			positions.push_back(buffer.substr(start,pos-start+1));
			buffer.erase(start,pos-start+1);
		}
		start = 0;
		locations.clear();
		for(string s : positions){
			start = s.find("x=\"");
			int x = atoi(s.substr(start+3,s.find("\" ",start)-start-3).c_str());
			start = s.find("y=\"");
			int y = atoi(s.substr(start+3,s.find("\" ",start)-start-3).c_str());
			start = s.find("w=\"");
			int w = atoi(s.substr(start+3,s.find("\" ",start)-start-3).c_str());
			start = s.find("h=\"");
			int h = atoi(s.substr(start+3,s.find("\" ",start)-start-3).c_str());
			SDL_Rect r = {x, y, w, h};
			locations.push_back(r);
		}
		curFrame = 0;
		numFrames = locations.size();
		endIndex = numFrames - 1;
		DisplayObject::setImage(images[startIndex]);
		DisplayObject::setRect(locations[curFrame]);
	}else{
		curFrame = startIndex;
		numFrames = a->numFrames;
		endIndex = a->endIndex;
		DisplayObject::setImage(images[startIndex]);
	}

	start = std::clock();
	playing = true;
	currAnimation = animName;
}

void AnimatedSprite::replay(){
	if(usesSheet){
		curFrame = -1;
		DisplayObject::setImage(images[startIndex]);
		DisplayObject::setRect(locations[0]);
	}else{
		curFrame = startIndex;
	}
}

void AnimatedSprite::stop(){
	playing = false;
	curFrame = 0;
	if(usesSheet){
		DisplayObject::setImage(images[startIndex]);
		DisplayObject::setRect(locations[0]);
	}else{
		DisplayObject::setImage(images[curFrame]);
	}
}

void AnimatedSprite::setFrameRate(int rate){
	frameRate = rate;
}

void AnimatedSprite::update(set<SDL_Scancode> pressedKeys){
	if(playing){
		std::clock_t end = std::clock();
		double duration = (( end - start ) / (double) CLOCKS_PER_SEC)*1000;
		if(duration > frameRate){
			start = end;

			if(curFrame < endIndex){
				curFrame++;
				if(usesSheet){
					DisplayObject::setRect(locations[curFrame]);
				}else{
					DisplayObject::setImage(images[curFrame]);
				}
			}else{
				if(loop){
					replay();
					return;
				}stop();
			}
		}
	}
}

void AnimatedSprite::draw(AffineTransform &at){
	Sprite::draw(at);
}

void AnimatedSprite::saveSelf(vector<string> &objects, vector<string> &dependencies) {
	string desc;
	stringstream sstm;
	int px0 = pivot.x, px1 = position.x, py0 = pivot.y, py1 = position.y;
	sstm << "4 " << id << " " << imgPath << " " << red << " " << green << " "
			<< blue << " " << std::boolalpha << vis << " " << std::boolalpha
			<< isRGB << " " << w << " " << h << " " << speed << " " << scaleX
			<< " " << scaleY << " " << rotation << " " << rotationAmount << " "
			<< alpha << " " << px0 << " " << py0 << " " << px1 << " " << py1
			<< "\n";
	desc = sstm.str();
	objects.push_back(desc);
	for (DisplayObject * child : children) {
			string dep = id + " " + child->id + "\n";
			dependencies.push_back(dep);
			child->saveSelf(objects, dependencies);
		}
}