
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include "three.h"

namespace THREE {

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

	THREE::Vector2* set(float x, float y);

	THREE::Vector2* setScalar(float scalar );

	THREE::Vector2* setX(float x );

	THREE::Vector2* setY(float y );

	THREE::Vector2* setComponent(int index, float value);

	float getComponent(int index );

	THREE::Vector2* clone();

	THREE::Vector2* copy(THREE::Vector2* v );

	THREE::Vector2* add(THREE::Vector2* v);

	THREE::Vector2* addScalar(float s );

	THREE::Vector2* addVectors(THREE::Vector2* a, THREE::Vector2* b );

	THREE::Vector2* addScaledVector(THREE::Vector2* v, float s );

	THREE::Vector2* sub(THREE::Vector2* v);

	THREE::Vector2* subScalar(float s );

	THREE::Vector2* subVectors(THREE::Vector2* a, THREE::Vector2* b );

	THREE::Vector2* multiply(THREE::Vector2* v );

	THREE::Vector2* multiplyScalar(float scalar );

	THREE::Vector2* divide(THREE::Vector2* v );

	THREE::Vector2* divideScalar(float scalar );

	THREE::Vector2* min(THREE::Vector2* v );

	THREE::Vector2* max(THREE::Vector2* v );

	THREE::Vector2* clamp(THREE::Vector2* min, THREE::Vector2* max );

	THREE::Vector2* clampScalar(float minVal, float maxVal);

	THREE::Vector2* clampLength(float min, float max);

	THREE::Vector2* floor();

	THREE::Vector2* ceil();

	THREE::Vector2* round();

	THREE::Vector2* roundToZero();

	THREE::Vector2* negate();

	float dot(THREE::Vector2* v );

	float lengthSq();

	float length();

	float lengthManhattan();

	THREE::Vector2* normalize();

	float angle();

	float distanceTo(THREE::Vector2* v );

	float distanceToSquared(THREE::Vector2* v );

	float distanceToManhattan(THREE::Vector2* v );

	THREE::Vector2* setLength(float length );

	THREE::Vector2* lerp(THREE::Vector2* v, float alpha );

	THREE::Vector2* lerpVectors(THREE::Vector2* v1, THREE::Vector2* v2, float alpha );

	bool equals(THREE::Vector2* v );

	THREE::Vector2* fromArray(std::vector<float> array, int offset );

	std::vector<float> toArray(std::vector<float> array, int offset );
/*
	THREE::Vector2* fromBufferAttribute(BufferAttribute* attribute, int index);
*/
	THREE::Vector2* rotateAround(THREE::Vector2* center, float angle);
};

};

#endif // _VECTOR2_H_
