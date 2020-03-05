#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#define PI 3.14159265

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <set>
#include "AffineTransform.h"
#include <string>
#include <fstream>
#include <vector>

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
	int numCopies = 0;

	DisplayObject();
	DisplayObject(string id, string path);
	DisplayObject(string id, int red, int green, int blue);
	virtual ~DisplayObject();
	
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	virtual void saveSelf(vector<string> &objects, vector<string> &dependencies);

	void loadTexture(string filepath);
	void loadRGBTexture(int red, int green, int blue);
	void setTexture(SDL_Texture* t);
	void setImage(SDL_Surface* img);
	void setID(string newId);
	string getID();
	void decreaseAlpha();
	void increaseAlpha();
	void setAlpha(int a);//added
	int getAlpha();
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
	void moveX(int x);
	void moveY(int y);
	void movePivot(int x, int y);
	void scaleIn();
	void scaleOut();
	void scale(double s);
	void setScale(double x, double y);//added
	void setScaleX(double x);
	void setScaleY(double y);
	double getScaleX();
	double getScaleY();
	void setRotation(double angle);
	void setRotationValue(double degrees);//added
	double getRotation();
	double getRotationDegrees();
	void rotateCW();
	void rotateCCW();
	double dist(SDL_Point &a, SDL_Point &b);
	void applyTransformations(AffineTransform &at);
	void reverseTransformations(AffineTransform &at);
	SDL_Point getPivot();
	SDL_Point getPosition();
	void setPosition(SDL_Point p);
	void setPivot(SDL_Point p);
	SDL_Point getWorld();
	SDL_Point getWorldCenter();
	bool isCopy;
	void setSpeed(int s);//added

private:
	

protected:
	
	int speed = 5;
	double scaleX = 1;
	double scaleY = 1;
	double rotation = 0; // radians
	double rotationAmount = 0.05; //radians
	int alpha;
	SDL_Point pivot, position, world, world_center;
	SDL_Texture* texture = NULL;
	SDL_Surface* image = NULL;
	/* Texture currently being drawn. Equal to texture for normal DO */
	SDL_Texture* curTexture;
};

#endif