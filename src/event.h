#ifndef _EVENT_H_
#define _EVENT_H_

//#include "three.h"


struct Event {
public:
	Event(string type) {
		this->type = type;
	}

	void* target;
	string type;
};



#endif // _EVENT_H_
