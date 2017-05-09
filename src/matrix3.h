
#ifndef _MATRIX3_H_
#define _MATRIX3_H_

#include "three.h"

namespace THREE {

class Matrix3 {
public:
	std::vector<float> elements;
	bool isMatrix3 = true;

	Matrix3();

	THREE::Matrix3* set(float n11, float n12, float n13, float n21, float n22, float n23, float n31, float n32, float n33);

	THREE::Matrix3* identity();

	THREE::Matrix3* clone();

	THREE::Matrix3* copy(THREE::Matrix3* m );

	THREE::Matrix3* setFromMatrix4(THREE::Matrix4* m );

	//BufferAttribute* applyToBufferAttribute(BufferAttribute* attribute);

	THREE::Matrix3* multiply(THREE::Matrix3* m );

	THREE::Matrix3* premultiply(THREE::Matrix3* m );

	THREE::Matrix3* multiplyMatrices(THREE::Matrix3* a, THREE::Matrix3* b );

	THREE::Matrix3* multiplyScalar(float s );

	float determinant();

	THREE::Matrix3* getInverse(THREE::Matrix3* matrix);

	THREE::Matrix3* getInverse(THREE::Matrix3* matrix, bool throwOnDegenerate );

	THREE::Matrix3* transpose();

	THREE::Matrix3* getNormalMatrix(THREE::Matrix4* matrix4 );

	THREE::Matrix3* transposeIntoArray(std::vector<float> &r);

	bool equals(THREE::Matrix3* matrix );

	THREE::Matrix3* fromArray(std::vector<float> arr);

	THREE::Matrix3* fromArray(std::vector<float> arr, int offset);

	std::vector<float> toArray(std::vector<float> arr, int offset);
};

};

#endif // _MATRIX3_H_
