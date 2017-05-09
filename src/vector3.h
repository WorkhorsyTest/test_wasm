
#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "three.h"

namespace THREE {

class Vector3 {
public:
	Vector3(float x, float y, float z);

	Vector3();

	THREE::Vector3* set(float x, float y, float z);

	THREE::Vector3* setScalar(float scalar );

	THREE::Vector3* setX(float x );

	THREE::Vector3* setY(float y );

	THREE::Vector3* setZ(float z );

	THREE::Vector3* setComponent(int index, float value);

	float getComponent(int index);

	THREE::Vector3* clone();

	THREE::Vector3* copy(THREE::Vector3* v );

	THREE::Vector3* add(THREE::Vector3* v);

	THREE::Vector3* add(THREE::Vector3* v, THREE::Vector3* w );

	THREE::Vector3* addScalar(float s );

	THREE::Vector3* addVectors(THREE::Vector3* a, THREE::Vector3* b);

	THREE::Vector3* addScaledVector(THREE::Vector3* v, float s);

	THREE::Vector3* sub(THREE::Vector3* v);

	THREE::Vector3* sub(THREE::Vector3* v, THREE::Vector3* w);

	THREE::Vector3* subScalar(float s );

	THREE::Vector3* subVectors(THREE::Vector3* a, THREE::Vector3* b);

	THREE::Vector3* multiply(THREE::Vector3* v, THREE::Vector3* w );

	THREE::Vector3* multiplyScalar(float scalar );

	THREE::Vector3* multiplyVectors(THREE::Vector3* a, THREE::Vector3* b);

	THREE::Vector3* applyEuler(THREE::Euler* euler);

	THREE::Vector3* applyAxisAngle(THREE::Vector3* axis, float angle);

	THREE::Vector3* applyMatrix3(THREE::Matrix3* m );

	THREE::Vector3* applyMatrix4(THREE::Matrix4* m );

	THREE::Vector3* applyProjection(THREE::Matrix4* m );

	THREE::Vector3* applyQuaternion(THREE::Quaternion* q );

//	void project(Camera* camera);

//	void unproject(Camera* camera);

	THREE::Vector3* transformDirection(THREE::Matrix4* m );

	THREE::Vector3* divide(THREE::Vector3* v );

	THREE::Vector3* divideScalar(float scalar );

	THREE::Vector3* min(THREE::Vector3* v );

	THREE::Vector3* max(THREE::Vector3* v );

	THREE::Vector3* clamp(THREE::Vector3* min, THREE::Vector3* max );

	THREE::Vector3* clampScalar(float minVal, float maxVal);

	THREE::Vector3* clampLength(float min, float max );

	THREE::Vector3* floor();

	THREE::Vector3* ceil();

	THREE::Vector3* round();

	THREE::Vector3* roundToZero();

	THREE::Vector3* negate();

	float dot(THREE::Vector3* v );

	float lengthSq();

	float length();

	float lengthManhattan();

	THREE::Vector3* normalize();

	THREE::Vector3* setLength(int length );

	THREE::Vector3* lerp(THREE::Vector3* v, float alpha );

	THREE::Vector3* erpVectors(THREE::Vector3* v1, THREE::Vector3* v2, float alpha );

	THREE::Vector3* cross(THREE::Vector3* v, THREE::Vector3* w );

	THREE::Vector3* crossVectors(THREE::Vector3* a, THREE::Vector3* b );

	THREE::Vector3* projectOnVector(THREE::Vector3* vector );

	THREE::Vector3* projectOnPlane(THREE::Vector3* planeNormal);

	THREE::Vector3* reflect(THREE::Vector3* normal);

	float angleTo(THREE::Vector3* v );

	float distanceTo(THREE::Vector3* v );

	float distanceToSquared(THREE::Vector3* v );

	float distanceToManhattan(THREE::Vector3* v );

	//THREE::Vector3* setFromSpherical(Spherical* s );

	THREE::Vector3* setFromMatrixPosition(THREE::Matrix4* m );

	THREE::Vector3* setFromMatrixScale(THREE::Matrix4* m );

	THREE::Vector3* setFromMatrixColumn(THREE::Matrix4* m, int index );

	bool equals(THREE::Vector3* v );

	THREE::Vector3* fromArray(std::vector<float> arr, int offset );

	std::vector<float> toArray(std::vector<float> arr, int offset );
/*
	THREE::Vector3* fromAttribute( attribute, int index, int offset );
*/
	float x;
	float y;
	float z;
	bool isVector3 = true;
};

};

#endif // _VECTOR3_H_
