#ifndef _EVENT_DISPATCHER_H_
#define _EVENT_DISPATCHER_H_

#include "three.h"


class EventDispatcher {
public:
	map<string, vector<void (*)(Event*)>> _listeners;

	void addEventListener(string type, void (*listener)(Event*));

	bool hasEventListener(string type, void (*listener)(Event*));

	void removeEventListener(string type, void (*listener)(Event*));

	void dispatchEvent( Event* event );
};


#endif // _EVENT_DISPATCHER_H_
