#include "EventDispatcher.h"
#include <iostream>
#include <algorithm>

EventDispatcher::EventDispatcher(){
	listeners = new std::unordered_map<std::string, std::vector<EventListener*>>;
}

EventDispatcher::~EventDispatcher(){
	//TODO: Find out if map destructor automatically frees container memory.
	for(auto it = listeners->begin(); it != listeners->end(); ++it){
		vector<EventListener*> l = it->second;

		for(EventListener* listener : l){
			// cerr << "addr of stuff: " << it->first << " " << listener << endl;
			if(listener){
				//delete listener;
				listener = NULL;
			}
		}
		l.clear();
	}
	delete listeners;
}

void EventDispatcher::addEventListener(EventListener* l, string eventType){
	// if(!(*listeners)[eventType])
	// 	(*listeners)[eventType] = new std::vector<EventListener*>;
	auto vec = (*listeners)[eventType];
	auto it = vec.begin();
	if((it = find(vec.begin(), vec.end(), l)) == vec.end())
		(*listeners)[eventType].push_back(l);
}

void EventDispatcher::removeEventListener(EventListener* l, string eventType){
	if(listeners->find(eventType) != listeners->end()){
		vector<EventListener*> *vec = &(*listeners)[eventType];
		for (auto it = vec->begin(); it != vec->end(); ++it){
			if(*it == l){
				// delete *it;
				auto loc = *it;
				vec->erase(it);
				if(find((*listeners)[eventType].begin(), (*listeners)[eventType].end(),loc)
					!= (*listeners)[eventType].end())
					printf("LISTER WAS NOT PROPERLY REMOVED FROM EVENTLIST\n");
				return;
			}
		}
	}

}

bool EventDispatcher::hasEventListener(EventListener* l, string eventType){
	auto it = listeners->find(eventType);
	return it != listeners->end();
}

void EventDispatcher::dispatchEvent(Event* e){
	if(listeners->count(e->getType()) == 0){
		cerr << "No listener with event type" << endl;
		return;
	}

	vector<EventListener*> l = (*listeners)[e->getType()];
	for (EventListener* listener : l){
		listener->handleEvent(e);
	}
}
