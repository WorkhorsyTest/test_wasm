


#include "Math.h"
#include <math.h>

const float Math::PI = M_PI;

float Math::Min(float a, float b) noexcept {
	return (a < b ? a : b);
}

float Math::Min(float a, float b, float c) noexcept {
	return Min(Min(a, b), c);
}

float Math::Max(float a, float b) noexcept {
	return (a > b ? a : b);
}

float Math::Max(float a, float b, float c) noexcept {
	return Max(Max(a, b), c);
}

float Math::Clamp(float value, float min, float max) noexcept {
	return Max(min, Min(max, value));
}

float Math::Asin(float x) noexcept {
	return asin(x);
}

float Math::Atan2(float a, float b) noexcept {
	return atan2(a, b);
}

float Math::Abs(float x) noexcept {
	return fabs(x);
}

float Math::Cos(float x) noexcept {
	return cos(x);
}

float Math::Acos(float x) noexcept {
	return acos(x);
}

float Math::Sin(float x) noexcept {
	return sin(x);
}

float Math::Sqrt(float x) noexcept {
	return sqrt(x);
}

float Math::Ceil(float x) noexcept {
	return ceil(x);
}

float Math::Floor(float x) noexcept {
	return floor(x);
}

float Math::Round(float x) noexcept {
	return round(x);
}

long Math::Pow(long base, long exponent) noexcept {
	return pow(base, exponent);
}

bool Math::IsNaN(float x) noexcept {
	return isnan(x);
}

bool Math::IsInfinity(float x) noexcept {
	return isfinite(x);
}

int Math::EuclideanModulo(int n, int m) {
	return ( ( n % m ) + m ) % m;
}

bool Math::IsInteger(const string &s) {
	if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
	char * p ;
	strtol(s.c_str(), &p, 10);
	return (*p == 0);
}

bool Math::IsFloat(const string &s) {
	std::istringstream iss(s);
	float f;
	iss >> noskipws >> f; // noskipws considers leading whitespace invalid
	// Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}

string Math::generateUUID() {
	// http://www.broofa.com/Tools/Math.uuid.htm
	const string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char uuid[36];
	int rnd = 0;
	int r = 0;

	for ( int i = 0; i < 36; i ++ ) {
		if ( i == 8 || i == 13 || i == 18 || i == 23 ) {
			uuid[ i ] = '-';
		} else if ( i == 14 ) {
			uuid[ i ] = '4';
		} else {
			if ( rnd <= 0x02 ) rnd = 0x2000000 + ( (rand() / RAND_MAX) * 0x1000000 ) | 0;
			r = rnd & 0xf;
			rnd = rnd >> 4;
			uuid[ i ] = chars[ ( i == 19 ) ? ( r & 0x3 ) | 0x8 : r ];
		}
	}
	return string(uuid);
}
