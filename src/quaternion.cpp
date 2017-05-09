

#include "three.h"

const int EPSILON = Math::Pow( 2, - 52 );

	Quaternion::Quaternion(float x, float y, float z, float w ) {
		this->_x = x;
		this->_y = y;
		this->_z = z;
		this->_w = w;
	}

	Quaternion::Quaternion() {
		this->_x = 0;
		this->_y = 0;
		this->_z = 0;
		this->_w = 1;
	}

	Quaternion* Quaternion::slerp(Quaternion* qa, Quaternion* qb, Quaternion* qm, float t ) {
		return qm->copy( qa )->slerp( qb, t );
	}

	void Quaternion::slerpFlat(float dst[], int dstOffset, float src0[], int srcOffset0, float src1[], int srcOffset1, float t ) {
		// fuzz-free, array-based Quaternion SLERP operation
		auto x0 = src0[ srcOffset0 + 0 ];
		auto y0 = src0[ srcOffset0 + 1 ];
		auto z0 = src0[ srcOffset0 + 2 ];
		auto w0 = src0[ srcOffset0 + 3 ];

		auto x1 = src1[ srcOffset1 + 0 ];
		auto y1 = src1[ srcOffset1 + 1 ];
		auto z1 = src1[ srcOffset1 + 2 ];
		auto w1 = src1[ srcOffset1 + 3 ];

		if ( w0 != w1 || x0 != x1 || y0 != y1 || z0 != z1 ) {

			auto s = 1 - t;
			auto cos = x0 * x1 + y0 * y1 + z0 * z1 + w0 * w1;
			auto dir = ( cos >= 0 ? 1 : - 1 );
			auto sqrSin = 1 - cos * cos;

			// Skip the Slerp for tiny steps to avoid numeric problems:
			if ( sqrSin > EPSILON ) {
				auto sin = Math::Sqrt( sqrSin );
				auto len = Math::Atan2( sin, cos * dir );

				s = Math::Sin( s * len ) / sin;
				t = Math::Sin( t * len ) / sin;
			}

			auto tDir = t * dir;

			x0 = x0 * s + x1 * tDir;
			y0 = y0 * s + y1 * tDir;
			z0 = z0 * s + z1 * tDir;
			w0 = w0 * s + w1 * tDir;

			// Normalize in case we just did a lerp:
			if ( s == 1 - t ) {

				auto f = 1 / Math::Sqrt( x0 * x0 + y0 * y0 + z0 * z0 + w0 * w0 );

				x0 *= f;
				y0 *= f;
				z0 *= f;
				w0 *= f;

			}

		}

		dst[ dstOffset ] = x0;
		dst[ dstOffset + 1 ] = y0;
		dst[ dstOffset + 2 ] = z0;
		dst[ dstOffset + 3 ] = w0;
	}

	float Quaternion::x() {
		return this->_x;
	}
	void Quaternion::x(float value ) {
		this->_x = value;
		this->onChangeCallback();
	}

	float Quaternion::y() {
		return this->_y;
	}
	void Quaternion::y(float value ) {
		this->_y = value;
		this->onChangeCallback();
	}

	float Quaternion::z() {
		return this->_z;
	}
	void Quaternion::z(float value ) {
		this->_z = value;
		this->onChangeCallback();
	}

	float Quaternion::w() {
		return this->_w;
	}
	void Quaternion::w(float value ) {
		this->_w = value;
		this->onChangeCallback();
	}

	Quaternion* Quaternion::set(float x, float y, float z, float w ) {
		this->_x = x;
		this->_y = y;
		this->_z = z;
		this->_w = w;

		this->onChangeCallback();

		return this;
	}

	Quaternion* Quaternion::clone() {
		return new Quaternion( this->_x, this->_y, this->_z, this->_w );
	}

	Quaternion* Quaternion::copy(Quaternion* quaternion ) {
		this->_x = quaternion->x();
		this->_y = quaternion->y();
		this->_z = quaternion->z();
		this->_w = quaternion->w();

		this->onChangeCallback();

		return this;
	}

	Quaternion* Quaternion::setFromEuler(Euler* euler) {
		return this->setFromEuler(euler, false);
	}

	Quaternion* Quaternion::setFromEuler(Euler* euler, bool update ) {
		auto x = euler->_x;
		auto y = euler->_y;
		auto z = euler->_z;
		auto order = euler->order();

		// http://www.mathworks.com/matlabcentral/fileexchange/
		// 	20696-function-to-convert-between-dcm-euler-angles-quaternions-and-euler-vectors/
		//	content/SpinCalc.m
		auto c1 = Math::Cos( x / 2 );
		auto c2 = Math::Cos( y / 2 );
		auto c3 = Math::Cos( z / 2 );

		auto s1 = Math::Sin( x / 2 );
		auto s2 = Math::Sin( y / 2 );
		auto s3 = Math::Sin( z / 2 );

		if ( order == "XYZ" ) {
			this->_x = s1 * c2 * c3 + c1 * s2 * s3;
			this->_y = c1 * s2 * c3 - s1 * c2 * s3;
			this->_z = c1 * c2 * s3 + s1 * s2 * c3;
			this->_w = c1 * c2 * c3 - s1 * s2 * s3;
		} else if ( order == "YXZ" ) {
			this->_x = s1 * c2 * c3 + c1 * s2 * s3;
			this->_y = c1 * s2 * c3 - s1 * c2 * s3;
			this->_z = c1 * c2 * s3 - s1 * s2 * c3;
			this->_w = c1 * c2 * c3 + s1 * s2 * s3;
		} else if ( order == "ZXY" ) {
			this->_x = s1 * c2 * c3 - c1 * s2 * s3;
			this->_y = c1 * s2 * c3 + s1 * c2 * s3;
			this->_z = c1 * c2 * s3 + s1 * s2 * c3;
			this->_w = c1 * c2 * c3 - s1 * s2 * s3;
		} else if ( order == "ZYX" ) {
			this->_x = s1 * c2 * c3 - c1 * s2 * s3;
			this->_y = c1 * s2 * c3 + s1 * c2 * s3;
			this->_z = c1 * c2 * s3 - s1 * s2 * c3;
			this->_w = c1 * c2 * c3 + s1 * s2 * s3;
		} else if ( order == "YZX" ) {
			this->_x = s1 * c2 * c3 + c1 * s2 * s3;
			this->_y = c1 * s2 * c3 + s1 * c2 * s3;
			this->_z = c1 * c2 * s3 - s1 * s2 * c3;
			this->_w = c1 * c2 * c3 - s1 * s2 * s3;
		} else if ( order == "XZY" ) {
			this->_x = s1 * c2 * c3 - c1 * s2 * s3;
			this->_y = c1 * s2 * c3 - s1 * c2 * s3;
			this->_z = c1 * c2 * s3 + s1 * s2 * c3;
			this->_w = c1 * c2 * c3 + s1 * s2 * s3;
		}

		if ( update != false ) this->onChangeCallback();

		return this;
	}

	Quaternion* Quaternion::setFromAxisAngle(Vector3* axis, float angle ) {
		// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/index.htm

		// assumes axis is normalized
		auto halfAngle = angle / 2;
		auto s = Math::Sin( halfAngle );

		this->_x = axis->x * s;
		this->_y = axis->y * s;
		this->_z = axis->z * s;
		this->_w = Math::Cos( halfAngle );

		this->onChangeCallback();

		return this;
	}

	Quaternion* Quaternion::setFromRotationMatrix(Matrix4* m ) {
		// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

		// assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)
		auto te = m->elements;

		float m11 = te[ 0 ];
		float m12 = te[ 4 ];
		float m13 = te[ 8 ];
		float m21 = te[ 1 ];
		float m22 = te[ 5 ];
		float m23 = te[ 9 ];
		float m31 = te[ 2 ];
		float m32 = te[ 6 ];
		float m33 = te[ 10 ];

		float trace = m11 + m22 + m33;
		float s;

		if ( trace > 0 ) {
			s = 0.5 / Math::Sqrt( trace + 1.0 );

			this->_w = 0.25 / s;
			this->_x = ( m32 - m23 ) * s;
			this->_y = ( m13 - m31 ) * s;
			this->_z = ( m21 - m12 ) * s;
		} else if ( m11 > m22 && m11 > m33 ) {
			s = 2.0 * Math::Sqrt( 1.0 + m11 - m22 - m33 );

			this->_w = ( m32 - m23 ) / s;
			this->_x = 0.25 * s;
			this->_y = ( m12 + m21 ) / s;
			this->_z = ( m13 + m31 ) / s;
		} else if ( m22 > m33 ) {
			s = 2.0 * Math::Sqrt( 1.0 + m22 - m11 - m33 );

			this->_w = ( m13 - m31 ) / s;
			this->_x = ( m12 + m21 ) / s;
			this->_y = 0.25 * s;
			this->_z = ( m23 + m32 ) / s;
		} else {
			s = 2.0 * Math::Sqrt( 1.0 + m33 - m11 - m22 );

			this->_w = ( m21 - m12 ) / s;
			this->_x = ( m13 + m31 ) / s;
			this->_y = ( m23 + m32 ) / s;
			this->_z = 0.25 * s;
		}

		this->onChangeCallback();

		return this;
	}

	Quaternion* Quaternion::setFromUnitVectors(Vector3* vFrom, Vector3* vTo) {
		// assumes direction vectors vFrom and vTo are normalized
		auto v1 = new Vector3();
		float r;

		const float EPS = 0.000001;

		if ( v1 == nullptr ) v1 = new Vector3();

		r = vFrom->dot( vTo ) + 1;

		if ( r < EPS ) {
			r = 0;
			if ( Math::Abs( vFrom->x ) > Math::Abs( vFrom->z ) ) {
				v1->set( - vFrom->y, vFrom->x, 0 );
			} else {
				v1->set( 0, - vFrom->z, vFrom->y );
			}
		} else {
			v1->crossVectors( vFrom, vTo );
		}

		this->_x = v1->x;
		this->_y = v1->y;
		this->_z = v1->z;
		this->_w = r;

		return this->normalize();
	}

	Quaternion* Quaternion::inverse() {
		return this->conjugate()->normalize();
	}

	Quaternion* Quaternion::conjugate() {
		this->_x *= - 1;
		this->_y *= - 1;
		this->_z *= - 1;

		this->onChangeCallback();

		return this;
	}

	float Quaternion::dot(Quaternion* v ) {
		return this->_x * v->_x + this->_y * v->_y + this->_z * v->_z + this->_w * v->_w;
	}

	float Quaternion::lengthSq() {
		return this->_x * this->_x + this->_y * this->_y + this->_z * this->_z + this->_w * this->_w;
	}

	int Quaternion::length() {
		return Math::Sqrt( this->_x * this->_x + this->_y * this->_y + this->_z * this->_z + this->_w * this->_w );
	}

	Quaternion* Quaternion::normalize() {
		auto l = this->length();

		if ( l == 0 ) {
			this->_x = 0;
			this->_y = 0;
			this->_z = 0;
			this->_w = 1;
		} else {
			l = 1 / l;

			this->_x = this->_x * l;
			this->_y = this->_y * l;
			this->_z = this->_z * l;
			this->_w = this->_w * l;
		}

		this->onChangeCallback();

		return this;
	}

	Quaternion* Quaternion::multiply(Quaternion* q) {
		return this->multiplyQuaternions(this, nullptr);
	}

	Quaternion* Quaternion::multiply(Quaternion* q, Quaternion* p ) {
		if ( p != nullptr ) {
			//console.warn( 'THREE.Quaternion: .multiply() now only accepts one argument. Use .multiplyQuaternions( a, b ) instead.' );
			return this->multiplyQuaternions( q, p );
		}

		return this->multiplyQuaternions( this, q );
	}

	Quaternion* Quaternion::premultiply(Quaternion* q ) {
		return this->multiplyQuaternions( q, this );
	}

	Quaternion* Quaternion::multiplyQuaternions(Quaternion* a, Quaternion* b ) {
		// from http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/code/index.htm
		auto qax = a->_x; auto qay = a->_y; auto qaz = a->_z; auto qaw = a->_w;
		auto qbx = b->_x; auto qby = b->_y; auto qbz = b->_z; auto qbw = b->_w;

		this->_x = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
		this->_y = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
		this->_z = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
		this->_w = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;

		this->onChangeCallback();

		return this;
	}

	Quaternion* Quaternion::slerp(Quaternion* qb, float t ) {
		if ( t == 0 ) return this;
		if ( t == 1 ) return this->copy( qb );

		auto x = this->_x, y = this->_y, z = this->_z, w = this->_w;

		// http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/

		auto cosHalfTheta = w * qb->_w + x * qb->_x + y * qb->_y + z * qb->_z;

		if ( cosHalfTheta < 0 ) {
			this->_w = - qb->_w;
			this->_x = - qb->_x;
			this->_y = - qb->_y;
			this->_z = - qb->_z;

			cosHalfTheta = - cosHalfTheta;
		} else {
			this->copy( qb );
		}

		if ( cosHalfTheta >= 1.0 ) {
			this->_w = w;
			this->_x = x;
			this->_y = y;
			this->_z = z;
			return this;
		}

		auto sinHalfTheta = Math::Sqrt( 1.0 - cosHalfTheta * cosHalfTheta );

		if ( Math::Abs( sinHalfTheta ) < 0.001 ) {
			this->_w = 0.5 * ( w + this->_w );
			this->_x = 0.5 * ( x + this->_x );
			this->_y = 0.5 * ( y + this->_y );
			this->_z = 0.5 * ( z + this->_z );
			return this;
		}

		auto halfTheta = Math::Atan2( sinHalfTheta, cosHalfTheta );
		auto ratioA = Math::Sin( ( 1 - t ) * halfTheta ) / sinHalfTheta,
			ratioB = Math::Sin( t * halfTheta ) / sinHalfTheta;

		this->_w = ( w * ratioA + this->_w * ratioB );
		this->_x = ( x * ratioA + this->_x * ratioB );
		this->_y = ( y * ratioA + this->_y * ratioB );
		this->_z = ( z * ratioA + this->_z * ratioB );

		this->onChangeCallback();

		return this;
	}

	bool Quaternion::equals(Quaternion* quaternion ) {
		return ( quaternion->_x == this->_x ) && ( quaternion->_y == this->_y ) && ( quaternion->_z == this->_z ) && ( quaternion->_w == this->_w );
	}

	Quaternion* Quaternion::fromArray(std::vector<float> arr) {
		return this->fromArray(arr, 0);
	}

	Quaternion* Quaternion::fromArray(std::vector<float> arr, int offset ) {
		this->_x = arr[ offset ];
		this->_y = arr[ offset + 1 ];
		this->_z = arr[ offset + 2 ];
		this->_w = arr[ offset + 3 ];

		this->onChangeCallback();

		return this;
	}

	std::vector<float> Quaternion::toArray(std::vector<float> arr, int offset ) {
//		if ( arr == nullptr ) arr = {};
//		if ( offset == nullptr ) offset = 0;

		arr[ offset ] = this->_x;
		arr[ offset + 1 ] = this->_y;
		arr[ offset + 2 ] = this->_z;
		arr[ offset + 3 ] = this->_w;

		return arr;
	}
/*
	Quaternion* onChange( callback ) {
		this->onChangeCallback = callback;

		return this;
	}
*/
	void Quaternion::onChangeCallback() {}
