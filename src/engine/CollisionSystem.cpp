#include "CollisionSystem.h"
#include "DTEvent.h"
#include <iostream>

double dist(SDL_Point &a, SDL_Point &b){
	return sqrt((b.y-a.y)*(b.y-a.y) + (b.x-a.x)*(b.x-a.x));
}

CollisionSystem::CollisionSystem(){

}

CollisionSystem::~CollisionSystem(){

}

bool compare_xval(DisplayObject* do1, DisplayObject* do2){
	if(!do1 || !do2)
		return -1;
	// Assuming getGlobalHitbox returns four points for the hitbox (tl, tr, br, bl)
	return (do1->getGlobalHitbox()[0].x < do2->getGlobalHitbox()[0].x);
}

//checks collisions between pairs of DOs where the corresponding types have been requested
//to be checked (via a single call to watchForCollisions) below.
void CollisionSystem::update(){
	/*
		Possible pseudocode:
			iterate through display objects:
				if collidesWith(DO1, DO2):
					if DO1 is Player and DO2 is Enemy:
						Dispatch event (to take damage or something)?
					if DO1 is Player and DO2 is Platform:
						resolveCollision()
					...
	*/	
}

//This system watches the game's display tree and is notified whenever a display object is placed onto
//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
void CollisionSystem::handleEvent(Event* e){
	objects.push_back(((DTEvent*) e)->getAddedObject());
	objects.sort(compare_xval);
	cout << "list is: ";
	for(auto it = objects.begin(); it != objects.end(); ++it){
		cout << (*it)->id << " ";
	}
	cout << "\n";
}

//This function asks the collision system to start checking for collisions between all pairs
//of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
//against all platform objects that are in the current scene.
void CollisionSystem::watchForCollisions(string type1, string type2){

}

/* Return:
	0 - Colinear
	1 - Right turn																																		
	-1 - Left turn
*/
int CollisionSystem::orientation(SDL_Point p1, SDL_Point q1, SDL_Point p2){
	int val = (q1.y - p1.y) * (p2.x - q1.x) - (q1.x - p1.x) * (p2.y - q1.y); 

    if(val < 0){ return -1;}
	if(val > 0){ return 1;}
	return 0;
}

bool CollisionSystem::onSeg(SDL_Point p1, SDL_Point p2, SDL_Point p3){
	return (p2.x <= max(p1.x, p3.x) && p2.x >= min(p1.x, p3.x) && p2.y <= max(p1.y, p3.y) && p2.y >= min(p1.y, p3.y)); 
}


bool CollisionSystem::intersect(SDL_Point p1, SDL_Point q1, SDL_Point p2, SDL_Point q2){
	int o1 = orientation(p1,q1,p2);
	int o2 = orientation(p1,q1,q2);
	int o3 = orientation(p2,q2,p1);
	int o4 = orientation(p2,q2,q1);

	if((o1 != o2) && (o3 != o4)){ return true;}

	if(o1 == 0 && onSeg(p1,p2,q1)) {return true;}
	if(o2 == 0 && onSeg(p1,q2,q1)) {return true;}
	if(o3 == 0 && onSeg(p2,p1,q2)) {return true;}
	if(o4 == 0 && onSeg(p2,q1,q2)) {return true;}
	return false;
	// Special case
}

double triangleArea(double s1, double s2, double s3){
	double p = (s1 + s2 + s3)/2;
	return sqrt(p*(p-s1)*(p-s2)*(p-s3));
}

bool checkArea(SDL_Point p, SDL_Point topL, SDL_Point topR, SDL_Point botL, SDL_Point botR, double w, double h){
	double area = 0;
	area += triangleArea(h,dist(p,topL),dist(p,botL));
	area += triangleArea(w,dist(p,topL),dist(p,topR));
	area += triangleArea(h,dist(p,topR),dist(p,botR));
	area += triangleArea(w,dist(p,botL),dist(p,botR));
	return area < ((w*h)+.0000001);
}


//returns true iff obj1 hitbox and obj2 hitbox overlap. Uses the following method from DO:
//SDL_Point* DisplayObject::getGlobalHitbox();
bool CollisionSystem::collidesWith(DisplayObject* obj1, DisplayObject* obj2){
	bool ret = true;
	AffineTransform *at1 = globalTransform(obj1);
	AffineTransform *at2 = globalTransform(obj2);

	double boundLow = 0.15;
	double boundHigh = 1 - boundLow;

	// SDL_Point topL1 = at1->transformPoint(obj1->w*boundLow,obj1->h*boundLow);
	// SDL_Point topR1 = at1->transformPoint(obj1->w*boundHigh,obj1->h*boundLow);
	// SDL_Point botL1 = at1->transformPoint(obj1->w*boundLow,obj1->h*boundHigh);
	// SDL_Point botR1 = at1->transformPoint(obj1->w*boundHigh,obj1->h*boundHigh);


	// SDL_Point topL2 = at2->transformPoint(obj2->w*boundLow,obj2->h*boundLow);
	// SDL_Point topR2 = at2->transformPoint(obj2->w*boundHigh,obj2->h*boundLow);
	// SDL_Point botL2 = at2->transformPoint(obj2->w*boundLow,obj2->h*boundHigh);
	// SDL_Point botR2 = at2->transformPoint(obj2->w*boundHigh,obj2->h*boundHigh);


	SDL_Point* p1 = obj1->getGlobalHitbox();
	SDL_Point topL1 = p1[0];
	SDL_Point topR1 = p1[1];
	SDL_Point botL1 = p1[3];
	SDL_Point botR1 = p1[2];

	SDL_Point* p2 = obj2->getGlobalHitbox();
	SDL_Point topL2 = p2[0];
	SDL_Point topR2 = p2[1];
	SDL_Point botL2 = p2[3];
	SDL_Point botR2 = p2[2];

	if((intersect(topL1,topR1,topL2,topR2) || intersect(topL1,topR1,topL2,botL2) || intersect(topL1,topR1,botR2,topR2) || intersect(topL1,topR1,botL2,botR2))){}
	else if((intersect(topR1,botR1,topL2,topR2) || intersect(topR1,botR1,topL2,botL2) || intersect(topR1,botR1,botR2,topR2) || intersect(topR1,botR1,botL2,botR2))){}
	else if((intersect(topL1,botL1,topL2,topR2) || intersect(topL1,botL1,topL2,botL2) || intersect(topL1,botL1,botR2,topR2) || intersect(topL1,botL1,botL2,botR2))){}
	else if((intersect(botL1,botR1,topL2,topR2) || intersect(botL1,botR1,topL2,botL2) || intersect(botL1,botR1,botR2,topR2) || intersect(botL1,botR1,botL2,botR2))){}
	else{ ret = false;}
	
	if(!ret){
		ret = checkArea(botR1,topL2,topR2,botL2,botR2,dist(topL2,topR2),dist(topL2,botL2)) || checkArea(botR2,topL1,topR1,botL1,botR1,dist(topL1,topR1),dist(topL1,botL1));
	}

	obj1->drawHitbox(*at1, ret);
	obj2->drawHitbox(*at2, ret);
	// obj1->drawHitbox(topL1,topR1,botL1,botR1,ret);
	// obj2->drawHitbox(topL2,topR2,botL2,botR2,ret);

	delete at1;
	delete at2;
	return ret;
}

//Resolves the collision that occurred between d and other
//xDelta1 and yDelta1 are the amount d moved before causing the collision.
//xDelta2 and yDelta2 are the amount other moved before causing the collision.
void CollisionSystem::resolveCollision(DisplayObject* d, DisplayObject* other, int xDelta1, int yDelta1, int xDelta2, int yDelta2){

}

AffineTransform* CollisionSystem::globalTransform(DisplayObject* o){
	//check references
	AffineTransform *at;
	if(o->parent != NULL){
		at = globalTransform(o->parent);
	}else{
		at = new AffineTransform();
	}o->applyTransformations(*at);
	return at;
}