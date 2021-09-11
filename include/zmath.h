#pragma once

namespace zmath {
	extern float epsilon;

	inline float radians(float degrees) { return degrees * 0.017453288f; }
	inline float degrees (float radians) { return radians * 57.29579143f; }

	bool isZero(float f);
}

