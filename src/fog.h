
#ifndef _FOG_H_
#define _FOG_H_

#include "three.h"

class Fog {
public:
	bool isFog;
	std::string name;
	Color* color;
	float near;
	float far;

	Fog(int color);

	Fog(int color, float near, float far);

	Fog* clone();
/*
	std::string toJSON( meta );
*/
};

#endif // _FOG_H_
