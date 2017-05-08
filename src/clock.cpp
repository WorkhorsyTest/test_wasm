

#include "three.h"

Clock::Clock() : Clock(true) {
}

Clock::Clock(bool autoStart) {
	this->autoStart = autoStart;

	this->startTime = 0;
	this->oldTime = 0;
	this->elapsedTime = 0;

	this->running = false;
}

void Clock::start() {
	this->startTime = Date::Now(); // see #10732

	this->oldTime = this->startTime;
	this->elapsedTime = 0;
	this->running = true;
}

void Clock::stop() {
	this->getElapsedTime();
	this->running = false;
}

long Clock::getElapsedTime() {
	this->getDelta();
	return this->elapsedTime;
}

long Clock::getDelta() {
	long diff = 0;

	if ( this->autoStart && ! this->running ) {
		this->start();
		return 0;
	}

	if ( this->running ) {
		long newTime = Date::Now();

		diff = ( newTime - this->oldTime ) / 1000;
		this->oldTime = newTime;

		this->elapsedTime += diff;
	}

	return diff;
}
