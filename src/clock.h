
#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "three.h"

class Clock {
public:
	bool autoStart;
	long startTime;
	long oldTime;
	long elapsedTime;
	bool running;

	Clock();

	Clock(bool autoStart);

	void start();

	void stop();

	long getElapsedTime();

	long getDelta();
};

#endif // _CLOCK_H_
