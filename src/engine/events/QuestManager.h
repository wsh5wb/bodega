#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H

#include "EventListener.h"

using namespace std;

class QuestManager : public EventListener {

public:
	QuestManager();
	void handleEvent(Event* e);
private:

};

#endif