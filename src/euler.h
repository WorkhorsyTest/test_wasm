
#ifndef _EULER_H_
#define _EULER_H_

#include "three.h"


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

	Euler* set(float x, float y, float z, std::string order );

	Euler* clone();

	Euler* copy(Euler* euler );

	Euler* setFromRotationMatrix(Matrix4* m, std::string order, bool update );

	Euler* setFromQuaternion(Quaternion* q, std::string order);

	Euler* setFromQuaternion(Quaternion* q, std::string order, bool update );

	Euler* setFromVector3(Vector3* v, std::string order );

	Euler* reorder(std::string newOrder);

	bool equals(Euler* euler );

	Euler* fromArray(std::vector<float> arr);

	std::vector<float> toArray(std::vector<float> arr, int offset );

	Vector3* toVector3(Vector3* optionalResult );
/*
	Euler* onChange( callback );
*/
	void onChangeCallback();
};

#endif // _EULER_H_
