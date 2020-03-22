#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#define PI 3.14159265

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <set>
#include "AffineTransform.h"
#include <string>
#include <fstream>

using namespace std;

class DisplayObject{

public:
	string id = "DEFAULT_ID";
	string imgPath = "";
	int red,green,blue;
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
	void setRect(SDL_Rect s);
	void decreaseAlpha();
	void increaseAlpha();
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
	SDL_Point getPivot();
	SDL_Point getPosition();

	int getAlpha();
	void setAlpha(int a);
	void setPosition(SDL_Point p);
	void setPivot(SDL_Point p);
	SDL_Point getWorld();
	SDL_Point getWorldCenter();
	bool isCopy;
	void setSpeed(int s);//added
	void setRenderer(SDL_Renderer* renderer);
	SDL_Renderer* getRenderer();
	SDL_Point* getGlobalHitbox();
	void drawHitbox(AffineTransform &at);

private:
	SDL_Texture* texture = NULL;
	SDL_Surface* image = NULL;
	/* Texture currently being drawn. Equal to texture for normal DO */
	SDL_Texture* curTexture;

protected:
	SDL_Rect srcrect;
	int speed = 5;
	double scaleX = 1;
	double scaleY = 1;
	double rotation = 0;
	double rotationAmount = 0.05;
	int alpha;
	SDL_Point pivot, position;
};

#endif