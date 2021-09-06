#pragma once

#include "vector3.h"

class Quaternion {
private:
	float _x;
	float _y;
	float _z;
	float _w;

public:

	enum RotationOrder {
		YXZ,
		ZYX,
		XYZ,
		ZXY,
		YZX,
		XZY
	};

	Quaternion() {
		_x = 0.f;
		_y = 0.f;
		_z = 0.f;
		_w = 1.f;
	}

	Quaternion(float x, float y, float z, float w) {
		_x = x;
		_y = y;
		_z = z;
		_w = w;
	}

	static Quaternion identity;

	static Quaternion fromEulerAngles(float x, float y, float z, RotationOrder order = RotationOrder::YXZ);

	Quaternion& normalize();

	inline float x() const { return _x; }
	inline void x(float __x) { _x = __x; }

	inline float y() const { return _y; }
	inline void y(float __y) { _y = __y; }

	inline float z() const { return _z; }
	inline void z(float __z) { _z = __z; }

	inline float w() const { return _w; }
	inline void w(float __w) { _w = __w; }

	float length() const;

	Vector3 operator * (const Vector3& v);
};
 