
#ifndef _FOG_H_
#define _FOG_H_

#include "three.h"

class Fog {
public:
	bool isFog;
	string name;
	Color* color;
	float near;
	float far;

	Fog(Color* color);

	Fog(Color* color, float near, float far);

	Fog* clone();
/*
	string toJSON( meta );
*/
};

#endif // _FOG_H_
