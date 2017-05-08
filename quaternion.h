
#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "three.h"

class Quaternion {
public:
	float _x;
	float _y;
	float _z;
	float _w;

	Quaternion(float x, float y, float z, float w );

	Quaternion();

	Quaternion* slerp(Quaternion* qa, Quaternion* qb, Quaternion* qm, float t );

	void slerpFlat(float dst[], int dstOffset, float src0[], int srcOffset0, float src1[], int srcOffset1, float t );

	float x();
	void x(float value );

	float y();
	void y(float value );

	float z();
	void z(float value );

	float w();
	void w(float value );

	Quaternion* set(float x, float y, float z, float w );

	Quaternion* clone();

	Quaternion* copy(Quaternion* quaternion );

	Quaternion* setFromEuler(Euler* euler);

	Quaternion* setFromEuler(Euler* euler, bool update );

	Quaternion* setFromAxisAngle(Vector3* axis, float angle );

	Quaternion* setFromRotationMatrix(Matrix4* m );

	Quaternion* setFromUnitVectors(Vector3* vFrom, Vector3* vTo);

	Quaternion* inverse();

	Quaternion* conjugate();

	float dot(Quaternion* v );

	float lengthSq();

	int length();

	Quaternion* normalize();

	Quaternion* multiply(Quaternion* q);

	Quaternion* multiply(Quaternion* q, Quaternion* p );

	Quaternion* premultiply(Quaternion* q );

	Quaternion* multiplyQuaternions(Quaternion* a, Quaternion* b );

	Quaternion* slerp(Quaternion* qb, float t );

	bool equals(Quaternion* quaternion );

	Quaternion* fromArray(vector<float> arr);

	Quaternion* fromArray(vector<float> arr, int offset );

	vector<float> toArray(vector<float> arr, int offset );
/*
	Quaternion* onChange( callback );
*/
	void onChangeCallback();
};

#endif // _QUATERNION_H_
