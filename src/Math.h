
#ifndef _MY_MATH_H_
#define _MY_MATH_H_

#include "Math.h"

class Math {
public:
	static float Min(float a, float b) noexcept;

	static float Max(float a, float b) noexcept;

	static float Clamp(float value, float min, float max) noexcept;

	static float Max(float a, float b, float c) noexcept;

	static float Asin(float x) noexcept;

	static float Atan2(float a, float b) noexcept;

	static float Abs(float x) noexcept;

	static float Cos(float x) noexcept;

	static float Acos(float x) noexcept;

	static float Sin(float x) noexcept;

	static float Sqrt(float x) noexcept;

	static float Ceil(float x) noexcept;

	static float Floor(float x) noexcept;

	static float Round(float x) noexcept;

	static long Pow(long base, long exponent) noexcept;

	static bool IsNaN(float x) noexcept;

	static bool IsInfinity(float x) noexcept;

	static int EuclideanModulo(int n, int m);
};

#endif // _MY_MATH_H_
