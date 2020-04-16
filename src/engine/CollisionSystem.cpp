#include "CollisionSystem.h"
#include "DTEvent.h"
#include "Game.h"
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include "Projectile.h"
#include "Player.h"

bool compare_xval(DORange_t do1, DORange_t do2){
	// Assuming getGlobalHitbox returns four points for the hitbox (tl, tr, br, bl)
	do1.x1 = do1.object->getGlobalHitbox()[0].x;
	do1.x2 = do1.object->getGlobalHitbox()[1].x;
	do2.x1 = do2.object->getGlobalHitbox()[0].x;
	do2.x2 = do2.object->getGlobalHitbox()[1].x;
	return (do1.x1 < do2.x2);
}

double dist(SDL_Point &a, SDL_Point &b){
	return sqrt((b.y-a.y)*(b.y-a.y) + (b.x-a.x)*(b.x-a.x));
}

CollisionSystem::CollisionSystem(){

}

CollisionSystem::~CollisionSystem(){

}

//checks collisions between pairs of DOs where the corresponding types have been requested
//to be checked (via a single call to watchForCollisions) below.
void CollisionSystem::update(){

	// TODO: come up with a better system for this later. It's trash right now
	for(string pair : pairs){
		size_t split = pair.find("-");
		string type1 = pair.substr(0,split);
		string type2 = pair.substr(split+1);

		vector vec1 = objects[type1];
		vector vec2 = objects[type2];
		// sort(vec1.begin(), vec1.end(), compare_xval);
		// sort(vec2.begin(), vec2.end(), compare_xval);
		int i = 0;
		for(DisplayObject* obj1 : vec1){
			for(DisplayObject* obj2 : vec2){
				if(obj1 == obj2)	continue;
				bool collision;
				i++;
				
				if((collision= collidesWith(obj1, obj2))){

					if(pair == "DOOR-PLAYER" || pair == "PLAYER-DOOR"){
						// assuming door1 is always S, 2 W, 3 N, 4 E
						char dir;
						if(obj1->id.substr(0,obj1->id.length()-1) == "Door")	dir = obj1->id[4];
						else													dir = obj2->id[4];

						switch(dir){
							case '1':{
								Event e("DUNG_TRANS_D", &Game::eventHandler);
								Game::eventHandler.dispatchEvent(&e);
								break;
							}
							case '2':{
								Event e("DUNG_TRANS_L", &Game::eventHandler);
								Game::eventHandler.dispatchEvent(&e);
								break;
							}
							case '3':{
								Event e("DUNG_TRANS_U", &Game::eventHandler);
								Game::eventHandler.dispatchEvent(&e);
								break;
							}
							case '4':{
								Event e("DUNG_TRANS_R", &Game::eventHandler);
								Game::eventHandler.dispatchEvent(&e);
								break;
							}
						}
						// printf("Door addr: %x\n", obj2);
						// cout << obj1->id << " collied with " << obj2->id << "   " << i << endl;
						
					}
					else if(type1 == "OBSTACLE" || type2 == "OBSTACLE"){
						printf("Player collided with obstacle\n");
						resolveObstacleCollision(obj1, obj2,
							obj1->deltaX, obj1->deltaY,
							obj2->deltaX, obj2->deltaY);

						// obj1->updateDelta(0,0,0,0,0);
						// obj2->updateDelta(0,0,0,0,0);
					}
					else{
						resolveCollision(obj1, obj2,
							obj1->deltaX, obj1->deltaY,
							obj2->deltaX, obj2->deltaY);

						// obj1->updateDelta(0,0,0,0,0);
						// obj2->updateDelta(0,0,0,0,0);
					}
				}
				// you can turn this into an event dispatch. Definitely would be a good idea.
				obj1->isCollided = collision;
				obj2->isCollided = collision;
			}
		}

	}
	// Handle user projectile/enemy collisions
	/*for(Projectile* p : Player::getPlayer()->projectiles){
		vector ens = objects["ENEMY"];
		for(DisplayObject* en : ens){
			if(collidesWith(p,en)){
				cout << en->id << " collied with " << "Projectile" << endl;
			}
		}
	}*/
}

//This system watches the game's display tree and is notified whenever a display object is placed onto
//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
void CollisionSystem::handleEvent(Event* e){
	DisplayObject* child = ((DTEvent*) e)->getAddedObject();

    string str;

	if(child->id.find("ENEMY") != string::npos)				str = "ENEMY";
	else if(child->id.find("PLAYER") != string::npos)		str = "PLAYER";
	else if(child->id.find("SETTING") != string::npos)		str = "SETTING";
	// TODO: Make a new OBJECT category?
	else if(child->id.find("Door") != string::npos)			str = "DOOR";
	else if(child->id.find("OBSTACLE") != string::npos)		str = "OBSTACLE";

	auto it = find(objects[str].begin(), objects[str].end(), child);

	if(e->getType() == "OBJ_ADD" && it == objects[str].end()){
		printf("Adding %s to DT\n", child->id.c_str());
		objects[str].push_back(child);
	}
	else if(e->getType() == "OBJ_RM")							objects[str].erase(it);

}

//This function asks the collision system to start checking for collisions between all pairs
//of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
//against all platform objects that are in the current scene.
void CollisionSystem::watchForCollisions(string type1, string type2){
	string pair = type1 + "-" + type2;
	if(find(pairs.begin(), pairs.end(), pair) != pairs.end())	return;

	pairs.push_back(pair);
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
	//cout << obj1->id << " " << obj2->id << endl;
	bool ret = true;
	//AffineTransform *at1 = globalTransform(obj1);
	//AffineTransform *at2 = globalTransform(obj2);

	double boundLow = 0.15;
	double boundHigh = 1 - boundLow;

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

	// if(ret){
	// 	//cout << obj1->deltaX << " " << obj1->deltaY << " " << obj2->deltaX << " " << obj2->deltaY << endl;
	// 	resolveCollision(obj1,obj2,obj1->deltaX,obj1->deltaY,obj2->deltaX,obj2->deltaY);
	// 	obj1->updateDelta(0,0,0,0,0);
	// 	obj2->updateDelta(0,0,0,0,0);
	// }

	// obj1->drawHitbox(*at1, ret);
	// obj2->drawHitbox(*at2, ret);

	//delete at1;
	//delete at2;
	return ret;
}

// prevCol = -1 for coming from a collision and 1 for not
void CollisionSystem::binarySearchX(DisplayObject* d, DisplayObject* other, int deltaX, bool sameDir, bool isCol){
	
	int n = (deltaX)/2;
	if(abs(n) <= 5 && !collidesWith(d,other)){
		return;
	}if(n == 0){
		n = 1;
	}
	if(!sameDir){
		n *= -1;
	}

	d->translate(n,0);
	
	if(collidesWith(d,other)){
		return binarySearchX(d,other,n,isCol,true);
	}else{
		return binarySearchX(d,other,n,!isCol,false);
	}

}

void CollisionSystem::binarySearchY(DisplayObject* d, DisplayObject* other, int deltaY, bool sameDir, bool isCol){
	
	int n = (deltaY)/2;
	if(abs(n) <= 5 && !collidesWith(d,other)){
		return;
	}if(n == 0){
		n = 1;
	}
	if(!sameDir){
		n *= -1;
	}

	d->translate(0,n);
	
	if(collidesWith(d,other)){
		return binarySearchY(d,other,n,isCol,true);
	}else{
		return binarySearchY(d,other,n,!isCol,false);
	}

}

void CollisionSystem::resolveObstacleCollision(DisplayObject* d, DisplayObject* other, int xDelta1, int yDelta1, int xDelta2, int yDelta2){
	//cout << xDelta1 << " " << yDelta1 << " " << xDelta2 << " " << yDelta2 << endl;


	if(xDelta1 != 0){
		d->translate(-xDelta1,0);
	}else if(xDelta2 != 0){
		other->translate(-xDelta2,0);
	}

	if(yDelta1 != 0){
		d->translate(0,-yDelta1);
	}else if(yDelta2 != 0){
		other->translate(0,-yDelta2);
	}
}
//Resolves the collision that occurred between d and other
//xDelta1 and yDelta1 are the amount d moved before causing the collision.
//xDelta2 and yDelta2 are the amount other moved before causing the collision.
void CollisionSystem::resolveCollision(DisplayObject* d, DisplayObject* other, int xDelta1, int yDelta1, int xDelta2, int yDelta2){
	/*if(xDelta1 != 0){
		/*for(int i = 0; i <5;i++){
			d->translate(-xDelta1/2,0);
		}*/
		//cout << "bs" << endl;
		//binarySearch(d,other,xDelta1,false,true);
		//d->translate(-xDelta1,0);
	/*	binarySearchX(d,other,xDelta1,false,true);
	}else if(xDelta2 != 0){
		//other->translate(-xDelta2,0);
		binarySearchX(other,d,xDelta2,false,true);
	}*/



	if(d->deltaScaleX != 0){
		d->setScaleX(d->scaleX/d->deltaScaleX);
	}if(other->deltaScaleX != 0){
		other->setScaleX(other->scaleX/other->deltaScaleX);
	}if(d->deltaScaleY != 0){
		d->setScaleY(d->scaleY/d->deltaScaleY);
	}if(other->deltaScaleY != 0){
		other->setScaleY(other->scaleY/other->deltaScaleY);
	}

	if(d->deltaRot != 0){
		d->rotate(-d->deltaRot);
	}if(other->deltaRot != 0){
		other->rotate(-other->deltaRot);
	}

	if(xDelta1 != 0){
		if(xDelta2 != 0 && other->speed > d->speed){
			binarySearchX(other,d,xDelta2,false,true);
		}else{
		/*for(int i = 0; i <5;i++){
			d->translate(-xDelta1/2,0);
		}*/
		//cout << "bs" << endl;
		//binarySearch(d,other,xDelta1,false,true);
		//d->translate(-xDelta1,0);
			binarySearchX(d,other,xDelta1,false,true);
		}
	}else if(xDelta2 != 0){
		//other->translate(-xDelta2,0);
		binarySearchX(other,d,xDelta2,false,true);
	}

	//cout << xDelta1 << " " << yDelta1 << " " << xDelta2 << " " << yDelta2 << endl;
	if(yDelta1 != 0){
		if(yDelta2 != 0 && other->speed > d->speed){
			binarySearchY(other,d,yDelta2,false,true);
		}else{
			binarySearchY(d,other,yDelta1,false,true);
		}
	}else if(yDelta2 != 0){
		//cout << "before" << other->getPosition().x << " " << other->getPosition().y << endl;
	//	other->translate(0,-yDelta2);
		//cout << other->getPosition().x << " " << other->getPosition().y << endl;
		binarySearchY(other,d,yDelta2,false,true);
	}
}

AffineTransform* CollisionSystem::globalTransform(DisplayObject* o){
	//check references
	AffineTransform *at;
	if(o->parent != NULL){
		at = globalTransform(o->parent);
	}else{
		at = new AffineTransform();
	}o->applyTransformations(*at);
	at->translate(-o->getPivot().x,-o->getPivot().y);

	return at;
}
