#pragma once
#pragma once

class Vector2 {
private:
	float _x;
	float _y;

public:

	static Vector2 zero;
	static Vector2 one;

	Vector2() {
	}

	Vector2(float x, float y) {
		set(x, y);
	}

	static Vector2 create(float x, float y);
	inline Vector2& set(float x, float y) {
		_x = x;
		_y = y;
		return *this;
	}

	inline float x() const { return _x; }
	inline void x(float __x) { _x = __x; }

	inline float y() const { return _y; }
	inline void y(float __y) { _y = __y; }

	inline float dot(const Vector2& other) const {
		return _x * other._x + _y * other._y;
	}

	float length() const;
	Vector2& normalize();

	inline Vector2 operator * (float f) const {
		return Vector2::create(_x * f, _y * f);
	}

	inline Vector2 operator + (const Vector2& other) const {
		return Vector2::create(_x + other._x, _y + other._y);
	}

	inline Vector2 operator - (const Vector2& other) const {
		return Vector2::create(_x - other._x, _y - other._y);
	}

	inline Vector2 operator / (float f) const {
		return this->operator*(1.f / f);
	}
};
