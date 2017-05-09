
#include "three.h"

namespace THREE {

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2::Vector2() : Vector2(0, 0) {
}

float Vector2::width() {
	return this->x;
}
void Vector2::width(float value ) {
	this->x = value;
}

float Vector2::height() {
	return this->y;
}
void Vector2::height(float value ) {
	this->y = value;
}

THREE::Vector2* Vector2::set(float x, float y) {
	this->x = x;
	this->y = y;
	return this;
}

THREE::Vector2* Vector2::setScalar(float scalar ) {
	this->x = scalar;
	this->y = scalar;
	return this;
}

THREE::Vector2* Vector2::setX(float x ) {
	this->x = x;
	return this;
}

THREE::Vector2* Vector2::setY(float y ) {
	this->y = y;
	return this;
}

THREE::Vector2* Vector2::setComponent(int index, float value) {
	switch ( index ) {
		case 0: this->x = value; break;
		case 1: this->y = value; break;
		default:
			std::ostringstream ss;
			ss << "index is out of range: " << index;
			throw ss.str();
	}

	return this;
}

float Vector2::getComponent(int index ) {
	switch ( index ) {
		case 0: return this->x;
		case 1: return this->y;
		default:
			std::ostringstream ss;
			ss << "index is out of range: " << index;
			throw ss.str();
	}
}

THREE::Vector2* Vector2::clone() {
	return new Vector2( this->x, this->y );
}

THREE::Vector2* Vector2::copy(THREE::Vector2* v ) {
	this->x = v->x;
	this->y = v->y;

	return this;
}

THREE::Vector2* Vector2::add(THREE::Vector2* v) {
	this->x += v->x;
	this->y += v->y;
	return this;
}

THREE::Vector2* Vector2::addScalar(float s ) {
	this->x += s;
	this->y += s;
	return this;
}

THREE::Vector2* Vector2::addVectors(THREE::Vector2* a, THREE::Vector2* b ) {
	this->x = a->x + b->x;
	this->y = a->y + b->y;
	return this;
}

THREE::Vector2* Vector2::addScaledVector(THREE::Vector2* v, float s ) {
	this->x += v->x * s;
	this->y += v->y * s;
	return this;
}

THREE::Vector2* Vector2::sub(THREE::Vector2* v) {
	this->x -= v->x;
	this->y -= v->y;
	return this;
}

THREE::Vector2* Vector2::subScalar(float s ) {
	this->x -= s;
	this->y -= s;
	return this;
}

THREE::Vector2* Vector2::subVectors(THREE::Vector2* a, THREE::Vector2* b ) {
	this->x = a->x - b->x;
	this->y = a->y - b->y;
	return this;
}

THREE::Vector2* Vector2::multiply(THREE::Vector2* v ) {
	this->x *= v->x;
	this->y *= v->y;
	return this;
}

THREE::Vector2* Vector2::multiplyScalar(float scalar ) {
	this->x *= scalar;
	this->y *= scalar;
	return this;
}

THREE::Vector2* Vector2::divide(THREE::Vector2* v ) {
	this->x /= v->x;
	this->y /= v->y;
	return this;
}

THREE::Vector2* Vector2::divideScalar(float scalar ) {
	return this->multiplyScalar( 1 / scalar );
}

THREE::Vector2* Vector2::min(THREE::Vector2* v ) {
	this->x = Math::Min( this->x, v->x );
	this->y = Math::Min( this->y, v->y );
	return this;
}

THREE::Vector2* Vector2::max(THREE::Vector2* v ) {
	this->x = Math::Max( this->x, v->x );
	this->y = Math::Max( this->y, v->y );
	return this;
}

THREE::Vector2* Vector2::clamp(THREE::Vector2* min, THREE::Vector2* max ) {
	// This function assumes min < max, if this assumption isn't true it will not operate correctly
	this->x = Math::Max( min->x, Math::Min( max->x, this->x ) );
	this->y = Math::Max( min->y, Math::Min( max->y, this->y ) );
	return this;
}

THREE::Vector2* Vector2::clampScalar(float minVal, float maxVal) {
	auto min = new Vector2();
	auto max = new Vector2();

	min->set( minVal, minVal );
	max->set( maxVal, maxVal );
	return this->clamp( min, max );
}

THREE::Vector2* Vector2::clampLength(float min, float max) {
	float length = this->length();
	return this->multiplyScalar( Math::Max( min, Math::Min( max, length ) ) / length );
}

THREE::Vector2* Vector2::floor() {
	this->x = Math::Floor( this->x );
	this->y = Math::Floor( this->y );
	return this;
}

THREE::Vector2* Vector2::ceil() {
	this->x = Math::Ceil( this->x );
	this->y = Math::Ceil( this->y );
	return this;
}

THREE::Vector2* Vector2::round() {
	this->x = Math::Round( this->x );
	this->y = Math::Round( this->y );
	return this;
}

THREE::Vector2* Vector2::roundToZero() {
	this->x = ( this->x < 0 ) ? Math::Ceil( this->x ) : Math::Floor( this->x );
	this->y = ( this->y < 0 ) ? Math::Ceil( this->y ) : Math::Floor( this->y );
	return this;
}

THREE::Vector2* Vector2::negate() {
	this->x = - this->x;
	this->y = - this->y;
	return this;
}

float Vector2::dot(THREE::Vector2* v ) {
	return this->x * v->x + this->y * v->y;
}

float Vector2::lengthSq() {
	return this->x * this->x + this->y * this->y;
}

float Vector2::length() {
	return Math::Sqrt( this->x * this->x + this->y * this->y );
}

float Vector2::lengthManhattan() {
	return Math::Abs( this->x ) + Math::Abs( this->y );
}

THREE::Vector2* Vector2::normalize() {
	return this->divideScalar( this->length() );
}

float Vector2::angle() {
	// computes the angle in radians with respect to the positive x-axis
	float angle = Math::Atan2( this->y, this->x );
	if ( angle < 0 ) angle += 2 * Math::PI;
	return angle;
}

float Vector2::distanceTo(THREE::Vector2* v ) {
	return Math::Sqrt( this->distanceToSquared( v ) );
}

float Vector2::distanceToSquared(THREE::Vector2* v ) {
	float dx = this->x - v->x;
	float dy = this->y - v->y;
	return dx * dx + dy * dy;
}

float Vector2::distanceToManhattan(THREE::Vector2* v ) {
	return Math::Abs( this->x - v->x ) + Math::Abs( this->y - v->y );
}

THREE::Vector2* Vector2::setLength(float length ) {
	return this->multiplyScalar( length / this->length() );
}

THREE::Vector2* Vector2::lerp(THREE::Vector2* v, float alpha ) {
	this->x += ( v->x - this->x ) * alpha;
	this->y += ( v->y - this->y ) * alpha;
	return this;
}

THREE::Vector2* Vector2::lerpVectors(THREE::Vector2* v1, THREE::Vector2* v2, float alpha ) {
	return this->subVectors( v2, v1 )->multiplyScalar( alpha )->add( v1 );
}

bool Vector2::equals(THREE::Vector2* v ) {
	return ( ( v->x == this->x ) && ( v->y == this->y ) );
}

THREE::Vector2* Vector2::fromArray(std::vector<float> array, int offset ) {
//		if ( offset == undefined ) offset = 0;
	this->x = array[ offset ];
	this->y = array[ offset + 1 ];
	return this;
}

std::vector<float> Vector2::toArray(std::vector<float> array, int offset ) {
//		if ( array == undefined ) array = [];
//		if ( offset == undefined ) offset = 0;

	array[ offset ] = this->x;
	array[ offset + 1 ] = this->y;

	return array;
}
/*
THREE::Vector2* fVector2::romBufferAttribute(BufferAttribute* attribute, int index) {
	this->x = attribute.getX( index );
	this->y = attribute.getY( index );

	return this;
}
*/
THREE::Vector2* Vector2::rotateAround(THREE::Vector2* center, float angle) {
	float c = Math::Cos( angle );
	float s = Math::Sin( angle );

	float x = this->x - center->x;
	float y = this->y - center->y;

	this->x = x * c - y * s + center->x;
	this->y = x * s + y * c + center->y;

	return this;
}

};
