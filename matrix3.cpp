


#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>

#include "matrix3.h"
#include "matrix4.h"
#include "vector3.h"
#include "quaternion.h"
#include "euler.h"
#include "object_3d.h"

using namespace std;

	Matrix3::Matrix3() {
		this->elements = {
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		};

		//if ( arguments.length > 0 ) {
			//console.error( 'THREE.Matrix3: the constructor no longer reads arguments. use .set() instead.' );
		//}
	}

	Matrix3* Matrix3::set(float n11, float n12, float n13, float n21, float n22, float n23, float n31, float n32, float n33) {
		auto te = this->elements;

		te[ 0 ] = n11; te[ 1 ] = n21; te[ 2 ] = n31;
		te[ 3 ] = n12; te[ 4 ] = n22; te[ 5 ] = n32;
		te[ 6 ] = n13; te[ 7 ] = n23; te[ 8 ] = n33;

		return this;
	}

	Matrix3* Matrix3::identity() {
		this->set(
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		);

		return this;
	}

	Matrix3* Matrix3::clone() {
		return (new Matrix3())->fromArray( this->elements );
	}

	Matrix3* Matrix3::copy(Matrix3* m ) {
		auto te = this->elements;
		auto me = m->elements;

		te[ 0 ] = me[ 0 ]; te[ 1 ] = me[ 1 ]; te[ 2 ] = me[ 2 ];
		te[ 3 ] = me[ 3 ]; te[ 4 ] = me[ 4 ]; te[ 5 ] = me[ 5 ];
		te[ 6 ] = me[ 6 ]; te[ 7 ] = me[ 7 ]; te[ 8 ] = me[ 8 ];

		return this;
	}

	Matrix3* Matrix3::setFromMatrix4(Matrix4* m ) {
		auto me = m->elements;

		this->set(
			me[ 0 ], me[ 4 ], me[  8 ],
			me[ 1 ], me[ 5 ], me[  9 ],
			me[ 2 ], me[ 6 ], me[ 10 ]
		);

		return this;
	}
/*
	BufferAttribute* Matrix3::applyToBufferAttribute(BufferAttribute* attribute) {
		auto v1 = new Vector3();

		for ( int i = 0, l = attribute->count; i < l; i ++ ) {
			v1.x = attribute->getX( i );
			v1.y = attribute->getY( i );
			v1.z = attribute->getZ( i );

			v1.applyMatrix3( this );

			attribute->setXYZ( i, v1.x, v1.y, v1.z );
		}

		return attribute;
	}
*/
	Matrix3* Matrix3::multiply(Matrix3* m ) {
		return this->multiplyMatrices( this, m );
	}

	Matrix3* Matrix3::premultiply(Matrix3* m ) {
		return this->multiplyMatrices( m, this );
	}

	Matrix3* Matrix3::multiplyMatrices(Matrix3* a, Matrix3* b ) {
		auto ae = a->elements;
		auto be = b->elements;
		auto te = this->elements;

		auto a11 = ae[ 0 ], a12 = ae[ 3 ], a13 = ae[ 6 ];
		auto a21 = ae[ 1 ], a22 = ae[ 4 ], a23 = ae[ 7 ];
		auto a31 = ae[ 2 ], a32 = ae[ 5 ], a33 = ae[ 8 ];

		auto b11 = be[ 0 ], b12 = be[ 3 ], b13 = be[ 6 ];
		auto b21 = be[ 1 ], b22 = be[ 4 ], b23 = be[ 7 ];
		auto b31 = be[ 2 ], b32 = be[ 5 ], b33 = be[ 8 ];

		te[ 0 ] = a11 * b11 + a12 * b21 + a13 * b31;
		te[ 3 ] = a11 * b12 + a12 * b22 + a13 * b32;
		te[ 6 ] = a11 * b13 + a12 * b23 + a13 * b33;

		te[ 1 ] = a21 * b11 + a22 * b21 + a23 * b31;
		te[ 4 ] = a21 * b12 + a22 * b22 + a23 * b32;
		te[ 7 ] = a21 * b13 + a22 * b23 + a23 * b33;

		te[ 2 ] = a31 * b11 + a32 * b21 + a33 * b31;
		te[ 5 ] = a31 * b12 + a32 * b22 + a33 * b32;
		te[ 8 ] = a31 * b13 + a32 * b23 + a33 * b33;

		return this;
	}

	Matrix3* Matrix3::multiplyScalar(float s ) {
		auto te = this->elements;

		te[ 0 ] *= s; te[ 3 ] *= s; te[ 6 ] *= s;
		te[ 1 ] *= s; te[ 4 ] *= s; te[ 7 ] *= s;
		te[ 2 ] *= s; te[ 5 ] *= s; te[ 8 ] *= s;

		return this;
	}

	float Matrix3::determinant() {
		auto te = this->elements;

		auto a = te[ 0 ];
		auto b = te[ 1 ];
		auto c = te[ 2 ];
		auto d = te[ 3 ];
		auto e = te[ 4 ];
		auto f = te[ 5 ];
		auto g = te[ 6 ];
		auto h = te[ 7 ];
		auto i = te[ 8 ];

		return a * e * i - a * f * h - b * d * i + b * f * g + c * d * h - c * e * g;
	}

	Matrix3* Matrix3::getInverse(Matrix3* matrix) {
		return this->getInverse(matrix, false);
	}

	Matrix3* Matrix3::getInverse(Matrix3* matrix, bool throwOnDegenerate ) {
		auto me = matrix->elements;
		auto te = this->elements;

		auto n11 = me[ 0 ];
		auto n21 = me[ 1 ];
		auto n31 = me[ 2 ];
		auto n12 = me[ 3 ];
		auto n22 = me[ 4 ];
		auto n32 = me[ 5 ];
		auto n13 = me[ 6 ];
		auto n23 = me[ 7 ];
		auto n33 = me[ 8 ];

		auto t11 = n33 * n22 - n32 * n23;
		auto t12 = n32 * n13 - n33 * n12;
		auto t13 = n23 * n12 - n22 * n13;

		auto det = n11 * t11 + n21 * t12 + n31 * t13;

		if ( det == 0 ) {
			if ( throwOnDegenerate == true ) {
				throw "THREE.Matrix3.getInverse(): can't invert matrix, determinant is 0";
			} else {
				//console.warn( msg );
			}
			return this->identity();
		}

		auto detInv = 1 / det;

		te[ 0 ] = t11 * detInv;
		te[ 1 ] = ( n31 * n23 - n33 * n21 ) * detInv;
		te[ 2 ] = ( n32 * n21 - n31 * n22 ) * detInv;

		te[ 3 ] = t12 * detInv;
		te[ 4 ] = ( n33 * n11 - n31 * n13 ) * detInv;
		te[ 5 ] = ( n31 * n12 - n32 * n11 ) * detInv;

		te[ 6 ] = t13 * detInv;
		te[ 7 ] = ( n21 * n13 - n23 * n11 ) * detInv;
		te[ 8 ] = ( n22 * n11 - n21 * n12 ) * detInv;

		return this;
	}

	Matrix3* Matrix3::transpose() {
		float tmp = 0;
		auto m = this->elements;

		tmp = m[ 1 ]; m[ 1 ] = m[ 3 ]; m[ 3 ] = tmp;
		tmp = m[ 2 ]; m[ 2 ] = m[ 6 ]; m[ 6 ] = tmp;
		tmp = m[ 5 ]; m[ 5 ] = m[ 7 ]; m[ 7 ] = tmp;

		return this;
	}

	Matrix3* Matrix3::getNormalMatrix(Matrix4* matrix4 ) {
		return this->setFromMatrix4( matrix4 )->getInverse( this )->transpose();
	}

	Matrix3* Matrix3::transposeIntoArray(vector<float> &r) {
		auto m = this->elements;

		r[ 0 ] = m[ 0 ];
		r[ 1 ] = m[ 3 ];
		r[ 2 ] = m[ 6 ];
		r[ 3 ] = m[ 1 ];
		r[ 4 ] = m[ 4 ];
		r[ 5 ] = m[ 7 ];
		r[ 6 ] = m[ 2 ];
		r[ 7 ] = m[ 5 ];
		r[ 8 ] = m[ 8 ];

		return this;
	}

	bool Matrix3::equals(Matrix3* matrix ) {
		auto te = this->elements;
		auto me = matrix->elements;

		for ( int i = 0; i < 9; i ++ ) {
			if ( te[ i ] != me[ i ] ) return false;
		}

		return true;
	}

	Matrix3* Matrix3::fromArray(vector<float> arr) {
		return this->fromArray(arr, 0);
	}

	Matrix3* Matrix3::fromArray(vector<float> arr, int offset) {
		for ( int i = 0; i < 9; i ++ ) {
			this->elements[ i ] = arr[ i + offset ];
		}

		return this;
	}

	vector<float> Matrix3::toArray(vector<float> arr, int offset) {
		//if ( arr == nullptr ) arr = {};
		//if ( offset == nullptr ) offset = 0;

		auto te = this->elements;

		arr[ offset ] = te[ 0 ];
		arr[ offset + 1 ] = te[ 1 ];
		arr[ offset + 2 ] = te[ 2 ];

		arr[ offset + 3 ] = te[ 3 ];
		arr[ offset + 4 ] = te[ 4 ];
		arr[ offset + 5 ] = te[ 5 ];

		arr[ offset + 6 ] = te[ 6 ];
		arr[ offset + 7 ] = te[ 7 ];
		arr[ offset + 8 ] = te[ 8 ];

		return arr;
	}
