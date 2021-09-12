#pragma once
#pragma once

namespace zmath {

	class Vector2 {
	public:

		static Vector2 zero;
		static Vector2 one;

		float x = 0.f;
		float y = 0.f;

		Vector2() = default;
		Vector2(float _x, float _y) {
			x = _x;
			y = _y;
		}

		inline float dot(const Vector2& other) const {
			return x * other.x + y * other.y;
		}

		float length() const;
		Vector2& normalize();

		inline Vector2 operator * (float f) const {
			return Vector2(x * f, y * f);
		}

		inline Vector2 operator + (const Vector2& other) const {
			return Vector2(x + other.x, y + other.y);
		}

		inline Vector2 operator - (const Vector2& other) const {
			return Vector2(x - other.x, y - other.y);
		}

		inline Vector2 operator / (float f) const {
			return this->operator*(1.f / f);
		}
	};
}
