
#ifndef _EULER_H_
#define _EULER_H_

#include "three.h"

namespace THREE {

class Euler {
public:
	float _x;
	float _y;
	float _z;
	std::string _order;
	bool isEuler = true;

	static const std::string DefaultOrder;

	static const std::string RotationOrders[];

	Euler(float x, float y, float z, std::string order);

	Euler();

	float x();

	void x(float value );

	float y();

	void y(float value );

	float z();

	void z(float value );

	std::string order();

	void order(std::string value );

	THREE::Euler* set(float x, float y, float z, std::string order );

	THREE::Euler* clone();

	THREE::Euler* copy(THREE::Euler* euler );

	THREE::Euler* setFromRotationMatrix(THREE::Matrix4* m, std::string order, bool update );

	THREE::Euler* setFromQuaternion(THREE::Quaternion* q, std::string order);

	THREE::Euler* setFromQuaternion(THREE::Quaternion* q, std::string order, bool update );

	THREE::Euler* setFromVector3(THREE::Vector3* v, std::string order );

	THREE::Euler* reorder(std::string newOrder);

	bool equals(THREE::Euler* euler );

	THREE::Euler* fromArray(std::vector<float> arr);

	std::vector<float> toArray(std::vector<float> arr, int offset );

	THREE::Vector3* toVector3(THREE::Vector3* optionalResult );
/*
	THREE::Euler* onChange( callback );
*/
	void onChangeCallback();
};

};

#endif // _EULER_H_
