
#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "three.h"

class Vector3 {
public:
	Vector3(float x, float y, float z);

	Vector3();

	Vector3* set(float x, float y, float z);

	Vector3* setScalar(float scalar );

	Vector3* setX(float x );

	Vector3* setY(float y );

	Vector3* setZ(float z );

	Vector3* setComponent(int index, float value);

	float getComponent(int index);

	Vector3* clone();

	Vector3* copy(Vector3* v );

	Vector3* add(Vector3* v);

	Vector3* add(Vector3* v, Vector3* w );

	Vector3* addScalar(float s );

	Vector3* addVectors(Vector3* a, Vector3* b);

	Vector3* addScaledVector(Vector3* v, float s);

	Vector3* sub(Vector3* v);

	Vector3* sub(Vector3* v, Vector3* w);

	Vector3* subScalar(float s );

	Vector3* subVectors(Vector3* a, Vector3* b);

	Vector3* multiply(Vector3* v, Vector3* w );

	Vector3* multiplyScalar(float scalar );

	Vector3* multiplyVectors(Vector3* a, Vector3* b);

	Vector3* applyEuler(Euler* euler);

	Vector3* applyAxisAngle(Vector3* axis, float angle);

	Vector3* applyMatrix3(Matrix3* m );

	Vector3* applyMatrix4(Matrix4* m );

	Vector3* applyProjection(Matrix4* m );

	Vector3* applyQuaternion(Quaternion* q );

//	void project(Camera* camera);

//	void unproject(Camera* camera);

	Vector3* transformDirection(Matrix4* m );

	Vector3* divide(Vector3* v );

	Vector3* divideScalar(float scalar );

	Vector3* min(Vector3* v );

	Vector3* max(Vector3* v );

	Vector3* clamp(Vector3* min, Vector3* max );

	Vector3* clampScalar(float minVal, float maxVal);

	Vector3* clampLength(float min, float max );

	Vector3* floor();

	Vector3* ceil();

	Vector3* round();

	Vector3* roundToZero();

	Vector3* negate();

	float dot(Vector3* v );

	float lengthSq();

	float length();

	float lengthManhattan();

	Vector3* normalize();

	Vector3* setLength(int length );

	Vector3* lerp(Vector3* v, float alpha );

	Vector3* erpVectors(Vector3* v1, Vector3* v2, float alpha );

	Vector3* cross(Vector3* v, Vector3* w );

	Vector3* crossVectors(Vector3* a, Vector3* b );

	Vector3* projectOnVector(Vector3* vector );

	Vector3* projectOnPlane(Vector3* planeNormal);

	Vector3* reflect(Vector3* normal);

	float angleTo(Vector3* v );

	float distanceTo(Vector3* v );

	float distanceToSquared(Vector3* v );

	float distanceToManhattan(Vector3* v );

	//Vector3* setFromSpherical(Spherical* s );

	Vector3* setFromMatrixPosition(Matrix4* m );

	Vector3* setFromMatrixScale(Matrix4* m );

	Vector3* setFromMatrixColumn(Matrix4* m, int index );

	bool equals(Vector3* v );

	Vector3* fromArray(vector<float> arr, int offset );

	vector<float> toArray(vector<float> arr, int offset );
/*
	Vector3* fromAttribute( attribute, int index, int offset );
*/
	float x;
	float y;
	float z;
	bool isVector3 = true;
};

#endif // _VECTOR3_H_
