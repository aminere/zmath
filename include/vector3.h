#pragma once

namespace zmath {

	class Vector3 {
	public:

		static Vector3 zero;
		static Vector3 one;
		static Vector3 forward;
		static Vector3 right;
		static Vector3 up;

		float x = 0.f;
		float y = 0.f;
		float z = 0.f;

		inline static Vector3 create(float x, float y, float z) {
			return { x, y, z };
		}

		Vector3() = default;
		Vector3(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
		}

		inline float dot(const Vector3& other) const {
			return x * other.x + y * other.y + z * other.z;
		}

		inline Vector3 operator * (float f) const {
			return Vector3::create(x * f, y * f, z * f);
		}

		inline Vector3 operator + (const Vector3& other) const {
			return Vector3::create(x + other.x, y + other.y, z + other.z);
		}

		inline Vector3 operator - (const Vector3& other) const {
			return Vector3::create(x - other.x, y - other.y, z - other.z);
		}

		inline Vector3 operator / (float f) const {
			return this->operator*(1.f / f);
		}

		float length() const;
		Vector3& normalize();
	};
}
