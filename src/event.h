
#ifndef _EVENT_H_
#define _EVENT_H_

#include <string>

namespace THREE {

//#include "three.h"


struct Event {
public:
	Event(std::string type) {
		this->type = type;
	}

	void* target;
	std::string type;
};

};

#endif // _EVENT_H_
