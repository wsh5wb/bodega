#include "DisplayObject.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include <iostream>
#include <algorithm>

DisplayObject::DisplayObject() {
	image = NULL;
	texture = NULL;
	curTexture = NULL;
	vis = true;
	alpha = 255;
	position.x = 0;
	position.y = 0;

	pivot.x = 0;
	pivot.y = 0;
	globalHitbox = new SDL_Point[4];
}

DisplayObject::DisplayObject(string id, string filepath){
	this->id = id;
	this->imgPath = filepath;
	loadTexture(filepath);
}

DisplayObject::DisplayObject(string id, string filepath, bool particle){
	this->id = id;
	this->imgPath = filepath;
	if(!particle){ globalHitbox = new SDL_Point[4];}

	loadTexture(filepath);
}

DisplayObject::DisplayObject(string id, int red, int green, int blue) {
	isRGB = true;
	this->id = id;

	this->red = red;
	this->blue = blue;
	this->green = green;
	globalHitbox = new SDL_Point[4];

	this->loadRGBTexture(red, green, blue);
}


DisplayObject::~DisplayObject(){
	if(image != NULL) SDL_FreeSurface(image);
	if(texture != NULL) SDL_DestroyTexture(texture);
}

void DisplayObject::loadTexture(string filepath) {
	image = IMG_Load(filepath.c_str());
	if (image == NULL) {
		printf("Bruh you done fucked up with the filepath. \n");
	}
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	setTexture(texture);
	w = image->w;
	h = image->h;
	srcrect = {0,0,w,h};
	vis = true;
	alpha = 255;
	position.x = 0;
	position.y = 0;
	pivot.x = 0;
	pivot.y = 0;
}

void DisplayObject::setImage(SDL_Surface *img) {
	image = img;
	if (texture != NULL)
		SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	setTexture(texture);
	w = image->w;
	h = image->h;
	srcrect = {0,0,w,h};
}

void DisplayObject::setRect(SDL_Rect s){
	w = s.w;
	h = s.h;
	srcrect = s;
}

void DisplayObject::loadRGBTexture(int red, int green, int blue) {
	image = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0x000000ff);
	SDL_FillRect(image, NULL, SDL_MapRGB(image->format, red, green, blue));
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	setTexture(texture);
}


void DisplayObject::loadRGBTexture(int red, int green, int blue, int w, int h){
	//cout << blue;
	isRGB = true;
	image = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	SDL_FillRect(image, NULL, SDL_MapRGB(image->format, red, green, blue));
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
	setTexture(texture);
}

void DisplayObject::setTexture(SDL_Texture* t){
	this->curTexture = t;
}

void DisplayObject::decreaseAlpha() {
	alpha -= 10;
	alpha = alpha < 0 ? 0 : alpha;
	SDL_SetTextureAlphaMod(curTexture, alpha);
}

void DisplayObject::increaseAlpha() {
	alpha += 10;
	alpha = alpha > 255 ? 255 : alpha;
	SDL_SetTextureAlphaMod(curTexture, alpha);
}

void DisplayObject::setAlpha(int a){
	alpha = a;
	if(a > 255){alpha = 255;}
	else if(a < 0){alpha = 0;}

	SDL_SetTextureAlphaMod(curTexture,alpha);
}

void DisplayObject::toggleVisibility(){
	vis = !vis;
}

void DisplayObject::makeVisible() {
	vis = true;
}

void DisplayObject::makeInvisible() {
	vis = false;
}

void DisplayObject::movePivotLeft() {
	pivot.x -= 2;
}

void DisplayObject::movePivotRight() {
	pivot.x += 2;
}

void DisplayObject::movePivotUp() {
	pivot.y -= 2;
}

void DisplayObject::movePivotDown() {
	pivot.y += 2;
}

void DisplayObject::translateRight() {
	position.x += speed;
	deltaX = speed;
}

void DisplayObject::translateLeft() {
	position.x -= speed;
	deltaX = -speed;
}

void DisplayObject::translateUp() {
	position.y -= speed;
	deltaY = -speed;
}

void DisplayObject::translateDown() {
	position.y += speed;
	deltaY = speed;
}

void DisplayObject::translate(int x, int y){
	position.x += x;
	position.y += y;
	deltaX = x;
	deltaY = y;
}

void DisplayObject::updateDelta(int x, int y, double scaleX, double scaleY, double rot){
	deltaX = x;
	deltaY = y;
	deltaScaleX = scaleX;
	deltaScaleY = scaleY;
	deltaRot = rot;
}

void DisplayObject::moveTo(int x, int y) {
	position.x = x;
	position.y = y;
}

void DisplayObject::movePivot(int x, int y) {
	pivot.x = x;
	pivot.y = y;
}

void DisplayObject::scaleIn() {
	scaleX *= .9;
	scaleY *= .9;
	deltaScaleX = .9;
	deltaScaleY = .9;
}

void DisplayObject::scaleOut() {
	scaleX *= 1.1;
	scaleY *= 1.1;
	deltaScaleX = 1.1;
	deltaScaleY = 1.1;
}

void DisplayObject::scale(double s) {
	scaleX *= s;
	scaleY *= s;
	deltaScaleX = s;
	deltaScaleY = s;
}

void DisplayObject::setScale(double x, double y){
	deltaScaleX = x/scaleX;
	deltaScaleY = y/scaleY;
	scaleX = x;
	scaleY = y;
}

void DisplayObject::setScaleX(double x){
	deltaScaleX = x/scaleX;
	scaleX = x;
	//deltaScaleX = x;
}

void DisplayObject::setScaleY(double y){
	deltaScaleY = y/scaleY;
	scaleY = y;
}

void DisplayObject::setRotation(double angle) {
	rotationAmount = angle * PI / 180;
}

void DisplayObject::setRotationValue(double degrees){
	rotationAmount = degrees*PI/180;
	while(rotation >= 2*PI){
		rotation -= 2*PI;
	}while(rotation < 0){
		rotation += 2*PI;
	}
}

double DisplayObject::getRotation(){
	return rotationAmount;
}

void DisplayObject::rotateCW() {
	rotation += rotationAmount;
	deltaRot = rotationAmount;
}

void DisplayObject::rotateCCW() {
	rotation -= rotationAmount;
	deltaRot = -rotationAmount;
}

void DisplayObject::rotate(double amount){
	rotation += amount;
	deltaRot = amount;
}

double DisplayObject::dist(SDL_Point &a, SDL_Point &b) {
	return sqrt((b.y - a.y) * (b.y - a.y) + (b.x - a.x) * (b.x - a.x));
}

SDL_Point DisplayObject::getPivot() {
	return this->pivot;
}

SDL_Point DisplayObject::getPosition() {
	return this->position;
}

int DisplayObject::getAlpha() {
	return this->alpha;
}

double DisplayObject::getScaleX() {
	return this->scaleX;
}

double DisplayObject::getScaleY() {
	return this->scaleY;
}

void DisplayObject::setSpeed(int s) {
	speed = s;
}

void DisplayObject::applyTransformations(AffineTransform &at) {
	at.translate(position.x, position.y);
	at.rotate(rotation);
	at.scale(scaleX, scaleY);
}

void DisplayObject::reverseTransformations(AffineTransform &at) {
	at.scale(1 / scaleX, 1 / scaleY);
	at.rotate(-rotation);
	at.translate(-position.x, -position.y);
}

void DisplayObject::update(set<SDL_Scancode> pressedKeys) {

}

void DisplayObject::draw(AffineTransform &at) {

	if (curTexture != NULL) {
		if (!vis) {
			return;
		}

		applyTransformations(at);

		at.translate(-pivot.x,-pivot.y);

		SDL_Point topL = at.transformPoint(0,0);
		SDL_Point topR = at.transformPoint(w,0);
		SDL_Point bottomR = at.transformPoint(w,h);

		SDL_Point pOrigin;
		pOrigin.x = 0; pOrigin.y = 0;

		int distAdj = dist(topL,topR);
		int distOpp = dist(topR,bottomR);
		SDL_Rect dstrect = { topL.x, topL.y, distAdj, distOpp};

		double angle = atan2(topR.y - topL.y, topR.x - topL.x) * 180 / PI;

		SDL_RenderCopyEx(Game::renderer, curTexture, NULL, &dstrect, angle,
				&pOrigin, SDL_FLIP_NONE);

		at.translate(pivot.x, pivot.y);

		reverseTransformations(at);

		if(showHitbox)	drawHitbox(isCollided);
	}

}

void DisplayObject::saveSelf(vector<string> &objects,
		vector<string> &dependencies) {
	string desc;
	stringstream sstm;
	int px0 = pivot.x, px1 = position.x, py0 = pivot.y, py1 = position.y;
	sstm << "1 " << id << " " << imgPath << " " << red << " " << green << " "
			<< blue << " " << std::boolalpha << vis << " " << std::boolalpha
			<< isRGB << " " << w << " " << h << " " << speed << " " << scaleX
			<< " " << scaleY << " " << rotation << " " << rotationAmount << " "
			<< alpha << " " << px0 << " " << py0 << " " << px1 << " " << py1
			<< "\n";
	desc = sstm.str();
	objects.push_back(desc);
}


void DisplayObject::drawHitbox(bool col){
	if(curTexture != NULL){
		if(!vis){return;}
		if(col){ SDL_SetRenderDrawColor(Game::renderer,0,255,0,255);}
		else{ SDL_SetRenderDrawColor(Game::renderer,255,0,0,255);}
		globalHitbox = getGlobalHitbox();
		//cout << id << " " << globalHitbox[0].x << " " << globalHitbox[1].x  << " " << w << endl;
		SDL_RenderDrawLine(Game::renderer,globalHitbox[0].x,globalHitbox[0].y,globalHitbox[1].x,globalHitbox[1].y);
		SDL_RenderDrawLine(Game::renderer,globalHitbox[0].x,globalHitbox[0].y,globalHitbox[3].x,globalHitbox[3].y);
		SDL_RenderDrawLine(Game::renderer,globalHitbox[3].x,globalHitbox[3].y,globalHitbox[2].x,globalHitbox[2].y);
		SDL_RenderDrawLine(Game::renderer,globalHitbox[2].x,globalHitbox[2].y,globalHitbox[1].x,globalHitbox[1].y);
		SDL_SetRenderDrawColor(Game::renderer,0,0,0,255);

		// this->globalHitbox[0] = hitbox[0];
		// this->globalHitbox[1] = hitbox[1];
		// this->globalHitbox[2] = hitbox[2];
		// this->globalHitbox[3] = hitbox[3];
	}
	// if(curTexture != NULL){
	// 	if(!vis){return;}

	// 	applyTransformations(at);
	// 	at.translate(-pivot.x,-pivot.y);

	// 	SDL_Point topL = at.transformPoint(0,0);
	// 	SDL_Point topR = at.transformPoint(w,0);
	// 	SDL_Point bottomR = at.transformPoint(w,h);

	// 	int distAdj = dist(topL,topR);
	// 	int distOpp = dist(topR,bottomR);

	// 	SDL_Rect dstrect = { topL.x, topL.y, w, h};

	// 	SDL_SetRenderDrawColor(Game::renderer,255,0,0,255);
	// 	SDL_RenderDrawRect(Game::renderer, &dstrect);
	// 	SDL_SetRenderDrawColor(Game::renderer,0,0,0,255);

	// 	at.translate(pivot.x,pivot.y);
	// 	reverseTransformations(at);

	// }
}

void DisplayObject::drawHitbox(SDL_Point topL, SDL_Point topR, SDL_Point bottomL, SDL_Point bottomR, bool col){
	if(curTexture != NULL){
		if(!vis){return;}
		if(col){ SDL_SetRenderDrawColor(Game::renderer,0,255,0,255);}
		else{ SDL_SetRenderDrawColor(Game::renderer,255,0,0,255);}
		SDL_RenderDrawLine(Game::renderer,topL.x,topL.y,topR.x,topR.y);
		SDL_RenderDrawLine(Game::renderer,topL.x,topL.y,bottomL.x,bottomL.y);
		SDL_RenderDrawLine(Game::renderer,bottomL.x,bottomL.y,bottomR.x,bottomR.y);
		SDL_RenderDrawLine(Game::renderer,bottomR.x,bottomR.y,topR.x,topR.y);
		SDL_SetRenderDrawColor(Game::renderer,0,0,0,255);

	}
}

void DisplayObject::setHitbox(SDL_Point* points){
	if(!this->hitbox)
		delete [] this->hitbox;

	this->hitbox = new SDL_Point[4];
	for(int i = 0; i < 4; i ++)
		this->hitbox[i] = points[i];
}

void DisplayObject::setHitbox(double boundLow, double boundHigh){
	SDL_Point charHit[4];
	charHit[0] = {(int)(w*boundLow),(int)(h*boundLow)};
	charHit[1] = {(int)(w*boundHigh),(int)(h*boundLow)};
	charHit[3] = {(int)(w*boundLow),(int)(h*boundHigh)};
	charHit[2] = {(int)(w*boundHigh),(int)(h*boundHigh)};

	setHitbox(charHit);

}


SDL_Point* DisplayObject::getGlobalHitbox(){
	if(!this->hitbox)
		return NULL;

	AffineTransform* at = getGlobalTransform(this);
	globalHitbox[0] = at->transformPoint(hitbox[0].x, hitbox[0].y);
	globalHitbox[1] = at->transformPoint(hitbox[1].x, hitbox[1].y);
	globalHitbox[2] = at->transformPoint(hitbox[2].x, hitbox[2].y);
	globalHitbox[3] = at->transformPoint(hitbox[3].x, hitbox[3].y);
	delete at;
	return globalHitbox;
}

AffineTransform* DisplayObject::getGlobalTransform(DisplayObject* o){
	AffineTransform *at;
	if(o->parent != NULL){
		at = getGlobalTransform(o->parent);
	} else{
		at = new AffineTransform();
	}
	o->applyTransformations(*at);
	return at;
}
