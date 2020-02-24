#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#define PI 3.14159265

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <set>
#include "sdlgui/AffineTransform.h"
#include <string>
#include <fstream>

using namespace std;

class DisplayObject{

public:
	string id = "DEFAULT_ID";
	string imgPath = "";
	int red,green,blue,alpha;
	string type = "DisplayObject";
	bool vis;
	bool isRGB = false;
	int w, h;

	DisplayObject();
	DisplayObject(string id, string path);
	DisplayObject(string id, int red, int green, int blue);
	virtual ~DisplayObject();
	
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	void loadTexture(string filepath);
	void loadRGBTexture(int red, int green, int blue);
	void setTexture(SDL_Texture* t);
	void setImage(SDL_Surface* img);
	void decreaseAlpha();
	void increaseAlpha();
	void setAlpha(int alpha);
	void toggleVisibility();
	void makeVisible();
	void makeInvisible();
	void movePivotLeft();
	void movePivotRight();
	void movePivotUp();
	void movePivotDown();
	void translateRight();
	void translateLeft();
	void translateUp();
	void translateDown();
	void moveTo(int x, int y);
	void movePivot(int x, int y);
	void scaleIn();
	void scaleOut();
	void scale(double s);
	void setRotation(double angle);
	double getRotation();
	void rotateCW();
	void rotateCCW();
	double dist(SDL_Point &a, SDL_Point &b);
	void applyTransformations(AffineTransform &at);
	void reverseTransformations(AffineTransform &at);
	SDL_Texture* getCurTexture();
	SDL_Point getPivot();
	SDL_Point getPosition();

private:
	

protected:
	
	int speed = 5;
	double scaleX = 1;
	double scaleY = 1;
	double rotation = 0;
	double rotationAmount = 0.05;
	SDL_Point pivot, position;
	SDL_Texture* texture = NULL;
	SDL_Surface* image = NULL;
	/* Texture currently being drawn. Equal to texture for normal DO */
	SDL_Texture* curTexture;

};

#endif