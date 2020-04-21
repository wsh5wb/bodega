#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#define PI 3.14159265

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <set>
#include "AffineTransform.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

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
	DisplayObject(string id, string path, bool particle);
	DisplayObject(string id, int red, int green, int blue);
	virtual ~DisplayObject();

	AffineTransform* getGlobalTransform(DisplayObject* o);
	virtual void resetDelta();
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	virtual void saveSelf(vector<string> &objects, vector<string> &dependencies);

	void loadTexture(string filepath);
	void loadRGBTexture(int red, int green, int blue);
	void loadRGBTexture(int red, int green, int blue, int w, int h);
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
	void translate(int x, int y);
	void moveTo(int x, int y);
	void movePivot(int x, int y);
	void scaleIn();
	void scaleOut();
	void scale(double s);

	void setScale(double x, double y);
	void setScaleX(double x);
	void setScaleY(double y);
	void setRotation(double angle);
	void setRotationValue(double degrees);

	double getRotation();
	void rotateCW();
	void rotateCCW();
	void rotate(double amount);
	double dist(SDL_Point &a, SDL_Point &b);
	void applyTransformations(AffineTransform &at);
	void reverseTransformations(AffineTransform &at);
	SDL_Point getPivot();
	SDL_Point getPosition();

	double getScaleX();
	double getScaleY();



	SDL_Color colorSDL(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
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
	void setHitbox(SDL_Point* points);
	void setHitbox(double boundLow, double boundHigh);
	void setHitbox(double boundLowX, double boundHighX, double boundLowY, double boundHighY);
	void drawHitbox(bool col);
	void drawHitbox(SDL_Point topL, SDL_Point topR, SDL_Point bottomL, SDL_Point bottomR, bool col);
	void updateDelta(int x, int y, double scaleX, double scaleY, double rot);
	DisplayObject * parent = NULL;
	int deltaX = 0;
	int deltaY = 0;
	double deltaRot = 0;
	double deltaScaleX = 0; double deltaScaleY = 0;
	bool showHitbox = false;
	bool isCollided = false;
	SDL_Point* hitbox;

	double scaleX = 1;
	double scaleY = 1;
	int speed = 5;

	int numEnemies = 0;

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Point pivot, position;
private:
	SDL_Texture* texture = NULL;
	SDL_Surface* image = NULL;
	/* Texture currently being drawn. Equal to texture for normal DO */
	SDL_Texture* curTexture;


protected:
	SDL_Rect srcrect;


	double rotation = 0;
	double rotationAmount = 0.05;
	int alpha;
	SDL_Point* globalHitbox;
};

#endif
