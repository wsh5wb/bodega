#ifndef ADDOBJECTEVENT_H
#define ADDOBJECTEVENT_H

#include "Event.h"
#include "DisplayObject.h"

using namespace std;

class DTEvent : public Event{
public:
	DTEvent(string type, EventDispatcher* source, DisplayObject* &do1) : Event(type, source){
		this->addedObject = do1;
	}

	~DTEvent(){
		
	}

	DisplayObject* getAddedObject(){
		return this->addedObject;
	}
private:
	DisplayObject* addedObject;
};

#endif