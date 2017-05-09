
#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "three.h"

namespace THREE {

class Quaternion {
public:
	float _x;
	float _y;
	float _z;
	float _w;

	Quaternion(float x, float y, float z, float w );

	Quaternion();

	THREE::Quaternion* slerp(THREE::Quaternion* qa, THREE::Quaternion* qb, THREE::Quaternion* qm, float t );

	void slerpFlat(float dst[], int dstOffset, float src0[], int srcOffset0, float src1[], int srcOffset1, float t );

	float x();
	void x(float value );

	float y();
	void y(float value );

	float z();
	void z(float value );

	float w();
	void w(float value );

	THREE::Quaternion* set(float x, float y, float z, float w );

	THREE::Quaternion* clone();

	THREE::Quaternion* copy(THREE::Quaternion* quaternion );

	THREE::Quaternion* setFromEuler(THREE::Euler* euler);

	THREE::Quaternion* setFromEuler(THREE::Euler* euler, bool update );

	THREE::Quaternion* setFromAxisAngle(THREE::Vector3* axis, float angle );

	THREE::Quaternion* setFromRotationMatrix(THREE::Matrix4* m );

	THREE::Quaternion* setFromUnitVectors(THREE::Vector3* vFrom, THREE::Vector3* vTo);

	THREE::Quaternion* inverse();

	THREE::Quaternion* conjugate();

	float dot(THREE::Quaternion* v );

	float lengthSq();

	int length();

	THREE::Quaternion* normalize();

	THREE::Quaternion* multiply(THREE::Quaternion* q);

	THREE::Quaternion* multiply(THREE::Quaternion* q, THREE::Quaternion* p );

	THREE::Quaternion* premultiply(THREE::Quaternion* q );

	THREE::Quaternion* multiplyQuaternions(THREE::Quaternion* a, THREE::Quaternion* b );

	THREE::Quaternion* slerp(THREE::Quaternion* qb, float t );

	bool equals(THREE::Quaternion* quaternion );

	THREE::Quaternion* fromArray(std::vector<float> arr);

	THREE::Quaternion* fromArray(std::vector<float> arr, int offset );

	std::vector<float> toArray(std::vector<float> arr, int offset );
/*
	THREE::Quaternion* onChange( callback );
*/
	void onChangeCallback();
};

};

#endif // _QUATERNION_H_
