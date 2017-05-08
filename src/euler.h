
#ifndef _EULER_H_
#define _EULER_H_

#include "three.h"


class Euler {
public:
	float _x;
	float _y;
	float _z;
	string _order;
	bool isEuler = true;

	static const string DefaultOrder;

	static const string RotationOrders[];

	Euler(float x, float y, float z, string order);

	Euler();

	float x();

	void x(float value );

	float y();

	void y(float value );

	float z();

	void z(float value );

	string order();

	void order(string value );

	Euler* set(float x, float y, float z, string order );

	Euler* clone();

	Euler* copy(Euler* euler );

	Euler* setFromRotationMatrix(Matrix4* m, string order, bool update );

	Euler* setFromQuaternion(Quaternion* q, string order);

	Euler* setFromQuaternion(Quaternion* q, string order, bool update );

	Euler* setFromVector3(Vector3* v, string order );

	Euler* reorder(string newOrder);

	bool equals(Euler* euler );

	Euler* fromArray(vector<float> arr);

	vector<float> toArray(vector<float> arr, int offset );

	Vector3* toVector3(Vector3* optionalResult );
/*
	Euler* onChange( callback );
*/
	void onChangeCallback();
};

#endif // _EULER_H_
