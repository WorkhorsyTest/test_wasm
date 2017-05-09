
#include "three.h"

namespace THREE {

	Vector3::Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3::Vector3() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	THREE::Vector3* Vector3::set(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;

		return this;
	}

	THREE::Vector3* Vector3::setScalar(float scalar ) {
		this->x = scalar;
		this->y = scalar;
		this->z = scalar;

		return this;
	}

	THREE::Vector3* Vector3::setX(float x ) {
		this->x = x;
		return this;
	}

	THREE::Vector3* Vector3::setY(float y ) {
		this->y = y;
		return this;
	}

	THREE::Vector3* Vector3::setZ(float z ) {
		this->z = z;
		return this;
	}

	THREE::Vector3* Vector3::setComponent(int index, float value) {
		switch ( index ) {
			case 0: this->x = value; break;
			case 1: this->y = value; break;
			case 2: this->z = value; break;
			default:
				std::ostringstream ss;
				ss << "index is out of range: " << index;
				throw ss.str();
		}

		return this;
	}

	float Vector3::getComponent(int index) {
		switch ( index ) {
			case 0: return this->x;
			case 1: return this->y;
			case 2: return this->z;
			default:
				std::ostringstream ss;
				ss << "index is out of range: " << index;
				throw ss.str();
		}
	}

	THREE::Vector3* Vector3::clone() {
		return new Vector3( this->x, this->y, this->z );
	}

	THREE::Vector3* Vector3::copy(THREE::Vector3* v ) {
		this->x = v->x;
		this->y = v->y;
		this->z = v->z;

		return this;
	}

	THREE::Vector3* Vector3::add(THREE::Vector3* v) {
		return this->add(v, nullptr);
	}

	THREE::Vector3* Vector3::add(THREE::Vector3* v, THREE::Vector3* w ) {
		if ( w != nullptr ) {
			//console.warn( 'THREE.Vector3: .add() now only accepts one argument. Use .addVectors( a, b ) instead.' );
			return this->addVectors( v, w );
		}

		this->x += v->x;
		this->y += v->y;
		this->z += v->z;

		return this;
	}

	THREE::Vector3* Vector3::addScalar(float s ) {
		this->x += s;
		this->y += s;
		this->z += s;

		return this;
	}

	THREE::Vector3* Vector3::addVectors(THREE::Vector3* a, THREE::Vector3* b) {
		this->x = a->x + b->x;
		this->y = a->y + b->y;
		this->z = a->z + b->z;

		return this;
	}

	THREE::Vector3* Vector3::addScaledVector(THREE::Vector3* v, float s) {
		this->x += v->x * s;
		this->y += v->y * s;
		this->z += v->z * s;

		return this;
	}

	THREE::Vector3* Vector3::sub(THREE::Vector3* v) {
		return this->sub(v, nullptr);
	}

	THREE::Vector3* Vector3::sub(THREE::Vector3* v, THREE::Vector3* w) {
		if ( w != nullptr ) {
			//console.warn( 'THREE.Vector3: .sub() now only accepts one argument. Use .subVectors( a, b ) instead.' );
			return this->subVectors( v, w );
		}

		this->x -= v->x;
		this->y -= v->y;
		this->z -= v->z;

		return this;
	}

	THREE::Vector3* Vector3::subScalar(float s ) {
		this->x -= s;
		this->y -= s;
		this->z -= s;

		return this;
	}

	THREE::Vector3* Vector3::subVectors(THREE::Vector3* a, THREE::Vector3* b) {
		this->x = a->x - b->x;
		this->y = a->y - b->y;
		this->z = a->z - b->z;

		return this;
	}

	THREE::Vector3* Vector3::multiply(THREE::Vector3* v, THREE::Vector3* w ) {
		if ( w != nullptr ) {
			//console.warn( 'THREE.Vector3: .multiply() now only accepts one argument. Use .multiplyVectors( a, b ) instead.' );
			return this->multiplyVectors( v, w );
		}

		this->x *= v->x;
		this->y *= v->y;
		this->z *= v->z;

		return this;
	}

	THREE::Vector3* Vector3::multiplyScalar(float scalar ) {
		if (! Math::IsNaN(scalar) && ! Math::IsInfinity(scalar)) {
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
		} else {
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}

		return this;
	}

	THREE::Vector3* Vector3::multiplyVectors(THREE::Vector3* a, THREE::Vector3* b) {
		this->x = a->x * b->x;
		this->y = a->y * b->y;
		this->z = a->z * b->z;

		return this;
	}

	THREE::Vector3* Vector3::applyEuler(THREE::Euler* euler) {
		THREE::Quaternion* quaternion = nullptr;

		if ( quaternion == nullptr ) quaternion = new Quaternion();

		return this->applyQuaternion( quaternion->setFromEuler( euler ) );
	}

	THREE::Vector3* Vector3::applyAxisAngle(THREE::Vector3* axis, float angle) {
		THREE::Quaternion* quaternion = nullptr;

		if ( quaternion == nullptr ) quaternion = new Quaternion();

		return this->applyQuaternion( quaternion->setFromAxisAngle( axis, angle ) );
	}

	THREE::Vector3* Vector3::applyMatrix3(THREE::Matrix3* m ) {
		auto x = this->x;
		auto y = this->y;
		auto z = this->z;
		auto e = m->elements;

		this->x = e[ 0 ] * x + e[ 3 ] * y + e[ 6 ] * z;
		this->y = e[ 1 ] * x + e[ 4 ] * y + e[ 7 ] * z;
		this->z = e[ 2 ] * x + e[ 5 ] * y + e[ 8 ] * z;

		return this;
	}

	THREE::Vector3* Vector3::applyMatrix4(THREE::Matrix4* m ) {
		// input: THREE.Matrix4 affine matrix
		auto x = this->x;
		auto y = this->y;
		auto z = this->z;
		auto e = m->elements;

		this->x = e[ 0 ] * x + e[ 4 ] * y + e[ 8 ]  * z + e[ 12 ];
		this->y = e[ 1 ] * x + e[ 5 ] * y + e[ 9 ]  * z + e[ 13 ];
		this->z = e[ 2 ] * x + e[ 6 ] * y + e[ 10 ] * z + e[ 14 ];

		return this;
	}

	THREE::Vector3* Vector3::applyProjection(THREE::Matrix4* m ) {
		// input: THREE.Matrix4 projection matrix
		auto x = this->x;
		auto y = this->y;
		auto z = this->z;
		auto e = m->elements;
		auto d = 1 / ( e[ 3 ] * x + e[ 7 ] * y + e[ 11 ] * z + e[ 15 ] ); // perspective divide

		this->x = ( e[ 0 ] * x + e[ 4 ] * y + e[ 8 ]  * z + e[ 12 ] ) * d;
		this->y = ( e[ 1 ] * x + e[ 5 ] * y + e[ 9 ]  * z + e[ 13 ] ) * d;
		this->z = ( e[ 2 ] * x + e[ 6 ] * y + e[ 10 ] * z + e[ 14 ] ) * d;

		return this;
	}

	THREE::Vector3* Vector3::applyQuaternion(THREE::Quaternion* q ) {
		auto x = this->x;
		auto y = this->y;
		auto z = this->z;
		auto qx = q->x();
		auto qy = q->y();
		auto qz = q->z();
		auto qw = q->w();

		// calculate quat * vector
		auto ix =  qw * x + qy * z - qz * y;
		auto iy =  qw * y + qz * x - qx * z;
		auto iz =  qw * z + qx * y - qy * x;
		auto iw = - qx * x - qy * y - qz * z;

		// calculate result * inverse quat
		this->x = ix * qw + iw * - qx + iy * - qz - iz * - qy;
		this->y = iy * qw + iw * - qy + iz * - qx - ix * - qz;
		this->z = iz * qw + iw * - qz + ix * - qy - iy * - qx;

		return this;
	}
/*
	void Vector3::project(Camera* camera) {
		THREE::Matrix4* matrix;

		if ( matrix == nullptr ) matrix = new Matrix4();

		matrix->multiplyMatrices( camera->projectionMatrix, matrix->getInverse( camera->matrixWorld ) );
		return this->applyProjection( matrix );
	}

	void Vector3::unproject(Camera* camera) {
		THREE::Matrix4* matrix;

		if ( matrix == nullptr ) matrix = new Matrix4();

		matrix->multiplyMatrices( camera->matrixWorld, matrix->getInverse( camera->projectionMatrix ) );
		return this->applyProjection( matrix );
	}
*/
	THREE::Vector3* Vector3::transformDirection(THREE::Matrix4* m ) {
		// input: THREE.Matrix4 affine matrix
		// vector interpreted as a direction
		auto x = this->x;
		auto y = this->y;
		auto z = this->z;
		auto e = m->elements;

		this->x = e[ 0 ] * x + e[ 4 ] * y + e[ 8 ]  * z;
		this->y = e[ 1 ] * x + e[ 5 ] * y + e[ 9 ]  * z;
		this->z = e[ 2 ] * x + e[ 6 ] * y + e[ 10 ] * z;

		return this->normalize();
	}

	THREE::Vector3* Vector3::divide(THREE::Vector3* v ) {
		this->x /= v->x;
		this->y /= v->y;
		this->z /= v->z;

		return this;
	}

	THREE::Vector3* Vector3::divideScalar(float scalar ) {
		return this->multiplyScalar( 1 / scalar );
	}

	THREE::Vector3* Vector3::min(THREE::Vector3* v ) {
		this->x = Math::Min( this->x, v->x );
		this->y = Math::Min( this->y, v->y );
		this->z = Math::Min( this->z, v->z );

		return this;
	}

	THREE::Vector3* Vector3::max(THREE::Vector3* v ) {
		this->x = Math::Max( this->x, v->x );
		this->y = Math::Max( this->y, v->y );
		this->z = Math::Max( this->z, v->z );

		return this;
	}

	THREE::Vector3* Vector3::clamp(THREE::Vector3* min, THREE::Vector3* max ) {
		// This function assumes min < max, if this assumption isn't true it will not operate correctly
		this->x = Math::Max( min->x, Math::Min( max->x, this->x ) );
		this->y = Math::Max( min->y, Math::Min( max->y, this->y ) );
		this->z = Math::Max( min->z, Math::Min( max->z, this->z ) );

		return this;
	}

	THREE::Vector3* Vector3::clampScalar(float minVal, float maxVal) {
		auto min = new Vector3();
		auto max = new Vector3();

		min->set( minVal, minVal, minVal );
		max->set( maxVal, maxVal, maxVal );

		return this->clamp( min, max );
	}

	THREE::Vector3* Vector3::clampLength(float min, float max ) {
		auto length = this->length();
		return this->multiplyScalar( Math::Max( min, Math::Min( max, length ) ) / length );
	}

	THREE::Vector3* Vector3::floor() {
		this->x = Math::Floor( this->x );
		this->y = Math::Floor( this->y );
		this->z = Math::Floor( this->z );

		return this;
	}

	THREE::Vector3* Vector3::ceil() {
		this->x = Math::Ceil( this->x );
		this->y = Math::Ceil( this->y );
		this->z = Math::Ceil( this->z );

		return this;
	}

	THREE::Vector3* Vector3::round() {
		this->x = Math::Round( this->x );
		this->y = Math::Round( this->y );
		this->z = Math::Round( this->z );

		return this;
	}

	THREE::Vector3* Vector3::roundToZero() {
		this->x = ( this->x < 0 ) ? Math::Ceil( this->x ) : Math::Floor( this->x );
		this->y = ( this->y < 0 ) ? Math::Ceil( this->y ) : Math::Floor( this->y );
		this->z = ( this->z < 0 ) ? Math::Ceil( this->z ) : Math::Floor( this->z );

		return this;
	}

	THREE::Vector3* Vector3::negate() {
		this->x = - this->x;
		this->y = - this->y;
		this->z = - this->z;

		return this;
	}

	float Vector3::dot(THREE::Vector3* v ) {
		return this->x * v->x + this->y * v->y + this->z * v->z;
	}

	float Vector3::lengthSq() {
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	float Vector3::length() {
		return Math::Sqrt( this->x * this->x + this->y * this->y + this->z * this->z );
	}

	float Vector3::lengthManhattan() {
		return Math::Abs( this->x ) + Math::Abs( this->y ) + Math::Abs( this->z );
	}

	THREE::Vector3* Vector3::normalize() {
		return this->divideScalar( this->length() );
	}

	THREE::Vector3* Vector3::setLength(int length ) {
		return this->multiplyScalar( length / this->length() );
	}

	THREE::Vector3* Vector3::lerp(THREE::Vector3* v, float alpha ) {
		this->x += ( v->x - this->x ) * alpha;
		this->y += ( v->y - this->y ) * alpha;
		this->z += ( v->z - this->z ) * alpha;

		return this;
	}

	THREE::Vector3* Vector3::erpVectors(THREE::Vector3* v1, THREE::Vector3* v2, float alpha ) {
		return this->subVectors( v2, v1 )->multiplyScalar( alpha )->add( v1 );
	}

	THREE::Vector3* Vector3::cross(THREE::Vector3* v, THREE::Vector3* w ) {
		if ( w != nullptr ) {
			//console.warn( 'THREE.Vector3: .cross() now only accepts one argument. Use .crossVectors( a, b ) instead.' );
			return this->crossVectors( v, w );
		}

		auto x = this->x;
		auto y = this->y;
		auto z = this->z;

		this->x = y * v->z - z * v->y;
		this->y = z * v->x - x * v->z;
		this->z = x * v->y - y * v->x;

		return this;
	}

	THREE::Vector3* Vector3::crossVectors(THREE::Vector3* a, THREE::Vector3* b ) {
		// FIXME: Does this assign the type for ay with auto?
		// Or is it really using an int?
		auto ax = a->x, ay = a->y, az = a->z;
		auto bx = b->x, by = b->y, bz = b->z;

		this->x = ay * bz - az * by;
		this->y = az * bx - ax * bz;
		this->z = ax * by - ay * bx;

		return this;
	}

	THREE::Vector3* Vector3::projectOnVector(THREE::Vector3* vector ) {
		auto scalar = vector->dot( this ) / vector->lengthSq();

		return this->copy( vector )->multiplyScalar( scalar );
	}

	THREE::Vector3* Vector3::projectOnPlane(THREE::Vector3* planeNormal) {
		auto v1 = new Vector3();

		v1->copy( this )->projectOnVector( planeNormal );
		return this->sub( v1 );
	}

	THREE::Vector3* Vector3::reflect(THREE::Vector3* normal) {
		// reflect incident vector off plane orthogonal to normal
		// normal is assumed to have unit length
		THREE::Vector3* v1 = nullptr;

		if ( v1 == nullptr ) v1 = new Vector3();

		return this->sub( v1->copy( normal )->multiplyScalar( 2 * this->dot( normal ) ) );
	}

	float Vector3::angleTo(THREE::Vector3* v ) {
		auto theta = this->dot( v ) / ( Math::Sqrt( this->lengthSq() * v->lengthSq() ) );

		// clamp, to handle numerical problems
		return Math::Acos( Math::Clamp( theta, - 1, 1 ) );
	}

	float Vector3::distanceTo(THREE::Vector3* v ) {
		return Math::Sqrt( this->distanceToSquared( v ) );
	}

	float Vector3::distanceToSquared(THREE::Vector3* v ) {
		auto dx = this->x - v->x;
		auto dy = this->y - v->y;
		auto dz = this->z - v->z;

		return dx * dx + dy * dy + dz * dz;
	}

	float Vector3::distanceToManhattan(THREE::Vector3* v ) {
		return Math::Abs( this->x - v->x ) + Math::Abs( this->y - v->y ) + Math::Abs( this->z - v->z );
	}
/*
	THREE::Vector3* Vector3::setFromSpherical(Spherical* s ) {
		auto sinPhiRadius = Math::Sin( s->phi ) * s->radius;

		this->x = sinPhiRadius * Math::Sin( s->theta );
		this->y = Math::Cos( s->phi ) * s->radius;
		this->z = sinPhiRadius * Math::Cos( s->theta );

		return this;
	}
*/
	THREE::Vector3* Vector3::setFromMatrixPosition(THREE::Matrix4* m ) {
		return this->setFromMatrixColumn( m, 3 );
	}

	THREE::Vector3* Vector3::setFromMatrixScale(THREE::Matrix4* m ) {
		auto sx = this->setFromMatrixColumn( m, 0 )->length();
		auto sy = this->setFromMatrixColumn( m, 1 )->length();
		auto sz = this->setFromMatrixColumn( m, 2 )->length();

		this->x = sx;
		this->y = sy;
		this->z = sz;

		return this;
	}

	THREE::Vector3* Vector3::setFromMatrixColumn(THREE::Matrix4* m, int index ) {
		return this->fromArray( m->elements, index * 4 );
	}

	bool Vector3::equals(THREE::Vector3* v ) {
		return ( ( v->x == this->x ) && ( v->y == this->y ) && ( v->z == this->z ) );
	}

	THREE::Vector3* Vector3::fromArray(std::vector<float> arr, int offset ) {
//		if ( offset == nullptr ) offset = 0;

		this->x = arr[ offset ];
		this->y = arr[ offset + 1 ];
		this->z = arr[ offset + 2 ];

		return this;
	}

	std::vector<float> Vector3::toArray(std::vector<float> arr, int offset ) {
//		if ( arr == nullptr ) arr = {};
//		if ( offset == nullptr ) offset = 0;

		arr[ offset ] = this->x;
		arr[ offset + 1 ] = this->y;
		arr[ offset + 2 ] = this->z;

		return arr;
	}
/*
	THREE::Vector3* Vector3::fromAttribute( attribute, int index, int offset ) {

		if ( offset == nullptr ) offset = 0;

		index = index * attribute.itemSize + offset;

		this->x = attribute.array[ index ];
		this->y = attribute.array[ index + 1 ];
		this->z = attribute.array[ index + 2 ];

		return this;
	}
*/
};
