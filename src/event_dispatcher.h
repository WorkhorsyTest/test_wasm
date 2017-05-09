
#ifndef _EVENT_DISPATCHER_H_
#define _EVENT_DISPATCHER_H_

#include "event.h"
#include "event_dispatcher.h"
#include <map>
#include <vector>
#include <string>

namespace THREE {

class EventDispatcher {
public:
	std::map<std::string, std::vector<void (*)(THREE::Event)>> _listeners;

	void addEventListener(std::string type, void (*listener)(THREE::Event));

	bool hasEventListener(std::string type, void (*listener)(THREE::Event));

	void removeEventListener(std::string type, void (*listener)(THREE::Event));

	void dispatchEvent( THREE::Event event );
};

};

#endif // _EVENT_DISPATCHER_H_
