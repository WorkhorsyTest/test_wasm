#ifndef _EVENT_DISPATCHER_H_
#define _EVENT_DISPATCHER_H_

#include "event.h"


class EventDispatcher {
public:
	std::map<std::string, std::vector<void (*)(Event)>> _listeners;

	void addEventListener(std::string type, void (*listener)(Event));

	bool hasEventListener(std::string type, void (*listener)(Event));

	void removeEventListener(std::string type, void (*listener)(Event));

	void dispatchEvent( Event event );
};


#endif // _EVENT_DISPATCHER_H_
