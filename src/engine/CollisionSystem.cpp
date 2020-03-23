#include "CollisionSystem.h"
#include <iostream>

CollisionSystem::CollisionSystem(){

}

CollisionSystem::~CollisionSystem(){

}

//checks collisions between pairs of DOs where the corresponding types have been requested
//to be checked (via a single call to watchForCollisions) below.
void CollisionSystem::update(){

}

//This system watches the game's display tree and is notified whenever a display object is placed onto
//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
void CollisionSystem::handleEvent(Event* e){

}

//This function asks the collision system to start checking for collisions between all pairs
//of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
//against all platform objects that are in the current scene.
void CollisionSystem::watchForCollisions(string type1, string type2){

}

//returns true iff obj1 hitbox and obj2 hitbox overlap. Uses the following method from DO:
//SDL_Point* DisplayObject::getGlobalHitbox();
bool CollisionSystem::collidesWith(DisplayObject* obj1, DisplayObject* obj2){
	//cout << "collide";
	AffineTransform at1 = *globalTransform(obj1);
	AffineTransform at2 = *globalTransform(obj2);

	/*SDL_Point topL1 = at1.transformPoint(0,0);
	SDL_Point topR1 = at1.transformPoint(obj1->w,0);
	SDL_Point botL1 = at1.transformPoint(0,obj1->h);
	SDL_Point botR1 = at1.transformPoint(obj1->w,obj1->h);*/

	SDL_Point topL1 = at1.transformPoint(obj1->w*0.15,obj1->h*.15);
	SDL_Point topR1 = at1.transformPoint(obj1->w*.85,obj1->h*.15);
	SDL_Point botL1 = at1.transformPoint(obj1->w*.15,obj1->h*.85);
	SDL_Point botR1 = at1.transformPoint(obj1->w*.85,obj1->h*.85);


	SDL_Point topL2 = at2.transformPoint(0,0);
	SDL_Point topR2 = at2.transformPoint(obj2->w,0);
	SDL_Point botL2 = at2.transformPoint(0,obj2->h);
	SDL_Point botR2 = at2.transformPoint(obj2->w,obj2->h);

	/*SDL_Rect * r1 = obj1->getGlobalHitbox();
	SDL_Rect * r2 = obj2->getGlobalHitbox();
	// Sides of rect 1
	int left1 = r1.x;
	int right1 = r1.x + r1.w;
	int top1 = r1.y;
	int bottom1 = r1.y + r1.h;

	// Sides of rect 2
	int left2 = r2.x;
	int right2 = r2.x + r2.w;
	int top2 = r2.y;
	int bottom2 = r2.y + r2.h;*/


	obj1->drawHitbox(topL1,topR1,botL1,botR1);
	obj2->drawHitbox(topL2,topR2,botL2,botR2);
	//cout << "collision" << endl;
	return true;
}

//Resolves the collision that occurred between d and other
//xDelta1 and yDelta1 are the amount d moved before causing the collision.
//xDelta2 and yDelta2 are the amount other moved before causing the collision.
void CollisionSystem::resolveCollision(DisplayObject* d, DisplayObject* other, int xDelta1, int yDelta1, int xDelta2, int yDelta2){

}

AffineTransform* CollisionSystem::globalTransform(DisplayObject* o){
	//check references
	AffineTransform *at = new AffineTransform();
	if(o->parent != NULL){
		at = globalTransform(o->parent);
	}o->applyTransformations(*at);
	return at;
}
