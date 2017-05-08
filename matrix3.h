
#ifndef _MATRIX3_H_
#define _MATRIX3_H_

#include "three.h"

class Matrix3 {
public:
	vector<float> elements;
	bool isMatrix3 = true;

	Matrix3();

	Matrix3* set(float n11, float n12, float n13, float n21, float n22, float n23, float n31, float n32, float n33);

	Matrix3* identity();

	Matrix3* clone();

	Matrix3* copy(Matrix3* m );

	Matrix3* setFromMatrix4(Matrix4* m );

	//BufferAttribute* applyToBufferAttribute(BufferAttribute* attribute);

	Matrix3* multiply(Matrix3* m );

	Matrix3* premultiply(Matrix3* m );

	Matrix3* multiplyMatrices(Matrix3* a, Matrix3* b );

	Matrix3* multiplyScalar(float s );

	float determinant();

	Matrix3* getInverse(Matrix3* matrix);

	Matrix3* getInverse(Matrix3* matrix, bool throwOnDegenerate );

	Matrix3* transpose();

	Matrix3* getNormalMatrix(Matrix4* matrix4 );

	Matrix3* transposeIntoArray(vector<float> &r);

	bool equals(Matrix3* matrix );

	Matrix3* fromArray(vector<float> arr);

	Matrix3* fromArray(vector<float> arr, int offset);

	vector<float> toArray(vector<float> arr, int offset);
};

#endif // _MATRIX3_H_
