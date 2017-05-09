
#ifndef _FOG_H_
#define _FOG_H_

#include "three.h"

namespace THREE {

class Fog {
public:
	bool isFog;
	std::string name;
	THREE::Color* color;
	float near;
	float far;

	Fog(int color);

	Fog(int color, float near, float far);

	THREE::Fog* clone();
/*
	std::string toJSON( meta );
*/
};

};

#endif // _FOG_H_
