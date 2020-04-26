#ifndef ITEMSYSTEM_H
#define ITEMSYSTEM_H

#include "EventListener.h"

#define RAND_ITEMS_NUM 11
using namespace std;

class ItemSystem: public EventListener{
public:
	void generateItem();
	int getItemCase();
	virtual void handleEvent(Event* e);

private:
	unsigned int chestsOpened = 0;
	unsigned int probList[RAND_ITEMS_NUM] = {20,9,1,10,5,2,10,20,3,15,5}; //tickets(or prob if out of 100)
	unsigned int totalChances = 100;
};

#endif