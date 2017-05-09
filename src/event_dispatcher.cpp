

#include "three.h"


void EventDispatcher::addEventListener(std::string type, void (*listener)(Event)) {
//		if ( this->_listeners == nullptr ) this->_listeners = {};

	auto listeners = this->_listeners;

	auto it = listeners.find(type);
	if (it == listeners.end()) {
		listeners[ type ] = {};
	}

	auto v = listeners[type];
	if (std::find(v.begin(), v.end(), listener) == v.end()) {
		listeners[ type ].push_back( listener );
	}
}

bool EventDispatcher::hasEventListener(std::string type, void (*listener)(Event)) {
//		if ( this->_listeners == nullptr ) return false;

	auto listeners = this->_listeners;

	auto it = listeners.find(type);
	if (it == listeners.end()) {
		return false;
	}

	auto v = listeners[type];
	return (std::find(v.begin(), v.end(), listener) != v.end());
}

void EventDispatcher::removeEventListener(std::string type, void (*listener)(Event)) {
//		if ( this->_listeners == nullptr ) return;

	auto listeners = this->_listeners;

	if (listeners.find(type) == listeners.end()) {
		return;
	}

	auto v = listeners[type];
	auto it = std::find(v.begin(), v.end(), listener);
	if (it != v.end()) {
		v.erase(it);
	}
}

void EventDispatcher::dispatchEvent( Event event ) {
//		if ( this->_listeners == nullptr ) return;

	auto listeners = this->_listeners;

	if (listeners.find(event.type) == listeners.end()) {
		return;
	}

	auto v = listeners[event.type];
	event.target = this;

	std::vector<void (*)(Event)> arr;
	for (size_t i=0; i<v.size(); ++i) {
		arr.push_back(v[i]);
	}

	for (size_t i=0; i<arr.size(); ++i) {
		arr[i](event);
	}
}
