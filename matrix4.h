
#ifndef _MATRIX4_H_
#define _MATRIX4_H_

class Euler;
class Matrix3;
class Matrix4;
class Quaternion;
class Vector3;

class Object3D;

#include "matrix3.h"
//#include "matrix4.h"
#include "vector3.h"
#include "quaternion.h"
#include "euler.h"
#include "object_3d.h"

using namespace std;

class Matrix4 {
public:
	Matrix4();

	Matrix4* set(float n11, float n12, float n13, float n14, float n21, float n22, float n23, float n24, float n31, float n32, float n33, float n34, float n41, float n42, float n43, float n44);

	Matrix4* identity();

	Matrix4* clone();

	Matrix4* copy(Matrix4*  m);

	Matrix4* copyPosition(Matrix4*  m);

	Matrix4* extractBasis(Vector3* xAxis, Vector3* yAxis, Vector3* zAxis);

	Matrix4* makeBasis(Vector3* xAxis, Vector3* yAxis, Vector3* zAxis);

	Matrix4* extractRotation(Matrix4* m);

	Matrix4* makeRotationFromEuler(Euler* euler);

	Matrix4* makeRotationFromQuaternion(Quaternion* q);

	Matrix4* lookAt(Vector3* eye, Vector3* target, Vector3* up);

	Matrix4* multiply(Matrix4* m, Matrix4* n);

	Matrix4* premultiply(Matrix4* m);

	Matrix4* multiplyMatrices(Matrix4* a, Matrix4* b);

	Matrix4* multiplyScalar(float s);
/*
	BufferAttribute* applyToBufferAttribute(BufferAttribute* attribute);
*/
	float determinant();

	Matrix4* transpose();

	Matrix4* setPosition(Vector3* v);

	Matrix4* getInverse(Matrix4* m);

	Matrix4* getInverse(Matrix4* m, bool throwOnDegenerate);

	Matrix4* scale(Vector3* v);

	float getMaxScaleOnAxis();

	Matrix4* makeTranslation(float x, float y, float z);

	Matrix4* makeRotationX(float theta);

	Matrix4* makeRotationY(float theta);

	Matrix4* makeRotationZ(float theta);

	Matrix4* makeRotationAxis(Vector3* axis, float angle);

	Matrix4* makeScale(float x, float y, float z);

	Matrix4* makeShear(float x, float y, float z);

	Matrix4* compose(Vector3* position, Quaternion* quaternion, Vector3* scale);

	Matrix4* decompose(Vector3* position, Quaternion* quaternion, Vector3* scale);

	Matrix4* makePerspective(float left, float right, float top, float bottom, float near, float far);

	Matrix4* makeOrthographic(float left, float right, float top, float bottom, float near, float far);

	bool equals(Matrix4* matrix);

	Matrix4* fromArray(vector<float> &array);

	Matrix4* fromArray(vector<float> &array, int offset);

	vector<float> toArray(vector<float> &array, int offset);

	bool isMatrix4 = true;
	vector<float> elements;
};

#endif // _MATRIX4_H_
