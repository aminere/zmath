
#include "pch.h"
#include "zmath.h"

namespace zmath {
	float epsilon = 0.000001f;

	bool isZero(float value) {
		return value > -epsilon && value < epsilon;
	}

	float lerp(float a, float b, float k) {
		return (b - a) * k + a;
	}

	float sign(float f) {
		return f < 0.f ? -1.f : 1.f;
	}
}
