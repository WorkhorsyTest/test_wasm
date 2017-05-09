
#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "three.h"

namespace THREE {

class Matrix4 {
public:
	Matrix4();

	THREE::Matrix4* set(float n11, float n12, float n13, float n14, float n21, float n22, float n23, float n24, float n31, float n32, float n33, float n34, float n41, float n42, float n43, float n44);

	THREE::Matrix4* identity();

	THREE::Matrix4* clone();

	THREE::Matrix4* copy(THREE::Matrix4*  m);

	THREE::Matrix4* copyPosition(THREE::Matrix4*  m);

	THREE::Matrix4* extractBasis(THREE::Vector3* xAxis, THREE::Vector3* yAxis, THREE::Vector3* zAxis);

	THREE::Matrix4* makeBasis(THREE::Vector3* xAxis, THREE::Vector3* yAxis, THREE::Vector3* zAxis);

	THREE::Matrix4* extractRotation(THREE::Matrix4* m);

	THREE::Matrix4* makeRotationFromEuler(THREE::Euler* euler);

	THREE::Matrix4* makeRotationFromQuaternion(THREE::Quaternion* q);

	THREE::Matrix4* lookAt(THREE::Vector3* eye, THREE::Vector3* target, THREE::Vector3* up);

	THREE::Matrix4* multiply(THREE::Matrix4* m, THREE::Matrix4* n);

	THREE::Matrix4* premultiply(THREE::Matrix4* m);

	THREE::Matrix4* multiplyMatrices(THREE::Matrix4* a, THREE::Matrix4* b);

	THREE::Matrix4* multiplyScalar(float s);
/*
	BufferAttribute* applyToBufferAttribute(BufferAttribute* attribute);
*/
	float determinant();

	THREE::Matrix4* transpose();

	THREE::Matrix4* setPosition(THREE::Vector3* v);

	THREE::Matrix4* getInverse(THREE::Matrix4* m);

	THREE::Matrix4* getInverse(THREE::Matrix4* m, bool throwOnDegenerate);

	THREE::Matrix4* scale(THREE::Vector3* v);

	float getMaxScaleOnAxis();

	THREE::Matrix4* makeTranslation(float x, float y, float z);

	THREE::Matrix4* makeRotationX(float theta);

	THREE::Matrix4* makeRotationY(float theta);

	THREE::Matrix4* makeRotationZ(float theta);

	THREE::Matrix4* makeRotationAxis(THREE::Vector3* axis, float angle);

	THREE::Matrix4* makeScale(float x, float y, float z);

	THREE::Matrix4* makeShear(float x, float y, float z);

	THREE::Matrix4* compose(THREE::Vector3* position, THREE::Quaternion* quaternion, THREE::Vector3* scale);

	THREE::Matrix4* decompose(THREE::Vector3* position, THREE::Quaternion* quaternion, THREE::Vector3* scale);

	THREE::Matrix4* makePerspective(float left, float right, float top, float bottom, float near, float far);

	THREE::Matrix4* makeOrthographic(float left, float right, float top, float bottom, float near, float far);

	bool equals(THREE::Matrix4* matrix);

	THREE::Matrix4* fromArray(std::vector<float> &array);

	THREE::Matrix4* fromArray(std::vector<float> &array, int offset);

	std::vector<float> toArray(std::vector<float> &array, int offset);

	bool isMatrix4 = true;
	std::vector<float> elements;
};

};

#endif // _MATRIX4_H_
