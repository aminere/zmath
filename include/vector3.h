#pragma once

class Vector3 {
private:
	float _x = 0.f;
	float _y = 0.f;
	float _z = 0.f;

public:

	static Vector3 zero;
	static Vector3 one;
	static Vector3 forward;
	static Vector3 right;
	static Vector3 up;

	static Vector3 create(float x, float y, float z);

	Vector3() = default;
	Vector3(float x, float y, float z) {
		set(x, y, z);
	}

	inline Vector3& set(float x, float y, float z) {
		_x = x;
		_y = y;
		_z = z;
		return *this;
	}

	inline float x() const { return _x; }
	inline void x(float __x) { _x = __x; }

	inline float y() const { return _y; }
	inline void y(float __y) { _y = __y; }

	inline float z() const { return _z; }
	inline void z(float __z) { _z = __z; }

	inline float dot(const Vector3& other) const {
		return _x * other._x + _y * other._y + _z * other._z;
	}

	inline Vector3 operator * (float f) const {
		return Vector3::create(_x * f, _y * f, _z * f);
	}

	inline Vector3 operator + (const Vector3& other) const {
		return Vector3::create(_x + other._x, _y + other._y, _z + other._z);
	}

	inline Vector3 operator - (const Vector3& other) const {
		return Vector3::create(_x - other._x, _y - other._y, _z - other._z);
	}

	inline Vector3 operator / (float f) const {
		return this->operator*(1.f / f);
	}

	float length() const;
	Vector3& normalize();
};
