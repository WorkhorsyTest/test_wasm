
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include "three.h"

class Vector2 {
public:
	float x;
	float y;

	Vector2(float x, float y);

	Vector2();

	float width();
	void width(float value );

	float height();
	void height(float value );

	Vector2* set(float x, float y);

	Vector2* setScalar(float scalar );

	Vector2* setX(float x );

	Vector2* setY(float y );

	Vector2* setComponent(int index, float value);

	float getComponent(int index );

	Vector2* clone();

	Vector2* copy(Vector2* v );

	Vector2* add(Vector2* v);

	Vector2* addScalar(float s );

	Vector2* addVectors(Vector2* a, Vector2* b );

	Vector2* addScaledVector(Vector2* v, float s );

	Vector2* sub(Vector2* v);

	Vector2* subScalar(float s );

	Vector2* subVectors(Vector2* a, Vector2* b );

	Vector2* multiply(Vector2* v );

	Vector2* multiplyScalar(float scalar );

	Vector2* divide(Vector2* v );

	Vector2* divideScalar(float scalar );

	Vector2* min(Vector2* v );

	Vector2* max(Vector2* v );

	Vector2* clamp(Vector2* min, Vector2* max );

	Vector2* clampScalar(float minVal, float maxVal);

	Vector2* clampLength(float min, float max);

	Vector2* floor();

	Vector2* ceil();

	Vector2* round();

	Vector2* roundToZero();

	Vector2* negate();

	float dot(Vector2* v );

	float lengthSq();

	float length();

	float lengthManhattan();

	Vector2* normalize();

	float angle();

	float distanceTo(Vector2* v );

	float distanceToSquared(Vector2* v );

	float distanceToManhattan(Vector2* v );

	Vector2* setLength(float length );

	Vector2* lerp(Vector2* v, float alpha );

	Vector2* lerpVectors(Vector2* v1, Vector2* v2, float alpha );

	bool equals(Vector2* v );

	Vector2* fromArray(std::vector<float> array, int offset );

	std::vector<float> toArray(std::vector<float> array, int offset );
/*
	Vector2* fromBufferAttribute(BufferAttribute* attribute, int index);
*/
	Vector2* rotateAround(Vector2* center, float angle);
};

#endif // _VECTOR2_H_
