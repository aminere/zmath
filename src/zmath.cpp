
#include "pch.h"
#include "zmath.h"

namespace zmath {
	float epsilon = 0.000001f;

	bool isZero(float value) {
		return value > -epsilon && value < epsilon;
	}
}
