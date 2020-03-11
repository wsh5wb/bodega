#include "DisplayObject.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include <iostream>
#include <algorithm>

DisplayObject::DisplayObject(){
	image = NULL;
	texture = NULL;
	curTexture = NULL;
	vis = true;
	alpha = 255;
	this->red = 0;
	this->green = 0;
	this->blue = 0;
	position.x = 0;
	position.y = 0;
	pivot.x = 0; pivot.y = 0;
	world = {0, 0};
	this->imgPath = "0";
	renderer = NULL;
}

DisplayObject::DisplayObject(string id, string filepath){
	this->id = id;
	this->imgPath = filepath;
	image = NULL;
	texture = NULL;
	curTexture = NULL;
	vis = true;
	alpha = 255;
	this->red = 0;
	this->green = 0;
	this->blue = 0;
	position.x = 0;
	position.y = 0;
	pivot.x = 0; pivot.y = 0;
	world = {0, 0};
	renderer = NULL;
	loadTexture(filepath);
}

DisplayObject::DisplayObject(string id, string filepath, SDL_Renderer* renderer){
	this->id = id;
	this->imgPath = filepath;
	image = NULL;
	texture = NULL;
	curTexture = NULL;
	vis = true;
	alpha = 255;
	this->red = 0;
	this->green = 0;
	this->blue = 0;
	position.x = 0;
	position.y = 0;
	pivot.x = 0; pivot.y = 0;
	world = {0, 0};
	setRenderer(renderer);
	loadTexture(filepath);
}

DisplayObject::DisplayObject(string id, int red, int green, int blue){
	isRGB = true;
	this->id = id;

	this->red = red;
	this->blue = blue;
	this->green = green;

	image = NULL;
	texture = NULL;
	curTexture = NULL;
	vis = true;
	alpha = 255;
	position.x = 0;
	position.y = 0;
	pivot.x = 0; pivot.y = 0;
	world = {0, 0};
	this->imgPath = "0";
	renderer = NULL;

	this->loadRGBTexture(red, green, blue);
}

DisplayObject::DisplayObject(string id, int red, int green, int blue, SDL_Renderer* renderer){
	isRGB = true;
	this->id = id;

	this->red = red;
	this->blue = blue;
	this->green = green;

	image = NULL;
	texture = NULL;
	curTexture = NULL;
	vis = true;
	alpha = 255;
	position.x = 0;
	position.y = 0;
	pivot.x = 0; pivot.y = 0;
	world = {0, 0};
	this->imgPath = "0";
	setRenderer(renderer);

	this->loadRGBTexture(red, green, blue);
}

DisplayObject::~DisplayObject(){
	if(image != NULL) SDL_FreeSurface(image);
	if(texture != NULL) SDL_DestroyTexture(texture);
	
}

void DisplayObject::loadTexture(string filepath){
	image = IMG_Load(filepath.c_str());
	if (image == NULL){
		printf("Bruh you done fucked up with the filepath. \n");
		return;
	}
	if(this->renderer == NULL)
		texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	else
		texture = SDL_CreateTextureFromSurface(renderer, image);

	setTexture(texture);
	w = image->w;
	h = image->h;
	vis = true;
	alpha = 255;
	position.x = 0;
	position.y = 0;
	pivot.x = 0; pivot.y = 0;
}

void DisplayObject::setImage(SDL_Surface* img){
	image = img;
	if(texture != NULL) SDL_DestroyTexture(texture);

	if(this->renderer == NULL)
		texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	else
		texture = SDL_CreateTextureFromSurface(renderer, image);

	setTexture(texture);
	w = image->w;
	h = image->h;
}

void DisplayObject::loadRGBTexture(int red, int green, int blue){
	image = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0x000000ff);
	SDL_FillRect(image, NULL, SDL_MapRGB(image->format, red, green, blue));

	if(this->renderer == NULL)
		texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	else
		texture = SDL_CreateTextureFromSurface(renderer, image);

	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
	setTexture(texture);
}

void DisplayObject::setTexture(SDL_Texture* t){
	this->curTexture = t;
}

void DisplayObject::setID(string newId){
	id = newId;
}

string DisplayObject::getID(){
	return id;
}

void DisplayObject::decreaseAlpha(){
	alpha -= 10;
	alpha = alpha < 0 ? 0 : alpha;
	SDL_SetTextureAlphaMod(curTexture,alpha);
}

void DisplayObject::increaseAlpha(){
	alpha += 10;
	alpha = alpha > 255 ? 255 : alpha;
	SDL_SetTextureAlphaMod(curTexture,alpha);
}

void DisplayObject::setAlpha(int a){
	alpha = a;
	if(a > 255){alpha = 255;}
	else if(a < 0){alpha = 0;}
	
	SDL_SetTextureAlphaMod(curTexture,alpha);
}

int DisplayObject::getAlpha(){
	return alpha;
}

void DisplayObject::toggleVisibility(){
	vis = !vis;
}

void DisplayObject::makeVisible(){
	vis = true;
}

void DisplayObject::makeInvisible(){
	vis = false;
}

void DisplayObject::movePivotLeft(){
	pivot.x -= 2;
}

void DisplayObject::movePivotRight(){
	pivot.x += 2;
}

void DisplayObject::movePivotUp(){
	pivot.y -= 2;
}

void DisplayObject::movePivotDown(){
	pivot.y += 2;
}

void DisplayObject::translateRight(){
	position.x += speed;
}

void DisplayObject::translateLeft(){
	position.x -= speed;
}

void DisplayObject::translateUp(){
	position.y -= speed;
}

void DisplayObject::translateDown(){
	position.y += speed;
}

void DisplayObject::moveTo(int x, int y){
	position.x = x;
	position.y = y;
}

void DisplayObject::moveX(int x){
	position.x = x;
}

void DisplayObject::moveY(int y){
	position.y = y;
}

void DisplayObject::movePivot(int x, int y){
	pivot.x = x;
	pivot.y = y;
}

void DisplayObject::scaleIn(){
	scaleX *= .9;
	scaleY *= .9;
}

void DisplayObject::scaleOut(){
	scaleX *= 1.1;
	scaleY *= 1.1;
}

void DisplayObject::scale(double s){
	scaleX *= s;
	scaleY *= s;
}

void DisplayObject::setScale(double x, double y){
	scaleX = x;
	scaleY = y;
}

void DisplayObject::setScaleX(double x){
	scaleX = x;
}

void DisplayObject::setScaleY(double y){
	scaleY = y;
}

double DisplayObject::getScaleX(){
	return scaleX;
}

double DisplayObject::getScaleY(){
	return scaleY;
}

void DisplayObject::setRotation(double angle){
	rotationAmount = angle*PI/180;
}

void DisplayObject::setRotationValue(double degrees){
	rotation = degrees*PI/180;
	while(rotation >= 2*PI){
		rotation -= 2*PI;
	}while(rotation < 0){
		rotation += 2*PI;
	}
}

double DisplayObject::getRotation(){
	return rotation;
}

double DisplayObject::getRotationDegrees(){
	return rotation * 180/PI;
}

void DisplayObject::rotateCW(){
	rotation += rotationAmount;
	while(rotation >= 2*PI){
		rotation -= 2*PI;
	}
}

void DisplayObject::rotateCCW(){
	rotation -= rotationAmount;
	while(rotation < 0){
		rotation += 2*PI;
	}
}

double DisplayObject::dist(SDL_Point &a, SDL_Point &b){
	return sqrt((b.y-a.y)*(b.y-a.y) + (b.x-a.x)*(b.x-a.x));
}

SDL_Point DisplayObject::getPivot(){
	return this->pivot;
}

SDL_Point DisplayObject::getPosition(){
	return this->position;
}

void DisplayObject::setPosition(SDL_Point p){
	position = p;
}

void DisplayObject::setPivot(SDL_Point p){
	pivot = p;
}

SDL_Point DisplayObject::getWorld(){
	return this->world;
}

SDL_Point DisplayObject::getWorldCenter(){
	return this->world_center;
}

void DisplayObject::setSpeed(int s){
	speed = s;
}

void DisplayObject::setRenderer(SDL_Renderer* renderer){
	this->renderer = renderer;
}

SDL_Renderer* DisplayObject::getRenderer(){
	return this->renderer;
}


void DisplayObject::applyTransformations(AffineTransform &at){
	at.translate(position.x,position.y);
	at.rotate(rotation);
	at.scale(scaleX,scaleY);
}

void DisplayObject::reverseTransformations(AffineTransform &at){
	at.scale(1/scaleX,1/scaleY);
	at.rotate(-rotation);
	at.translate(-position.x,-position.y);
}

void DisplayObject::update(set<SDL_Scancode> pressedKeys){

}

void DisplayObject::draw(AffineTransform &at){

	if(curTexture != NULL){
		if(!vis){return;}

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
		world = {topL.x, topL.y};
		world_center = {topL.x + distAdj/2, topL.y + distOpp/2};
		double angle = atan2(topR.y-topL.y,topR.x-topL.x)*180/PI;

		if(this->renderer == NULL)
			SDL_RenderCopyEx(Game::renderer, curTexture, NULL, &dstrect, angle, &pOrigin, SDL_FLIP_NONE);	
		else
			SDL_RenderCopyEx(this->renderer, curTexture, NULL, &dstrect, angle, &pOrigin, SDL_FLIP_NONE);	
		at.translate(pivot.x,pivot.y);
		reverseTransformations(at);

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