#pragma once

#include "vector2.h"

namespace zmath {

	class Matrix44;

	class Vector3 {
	public:

		static Vector3 zero;
		static Vector3 one;
		static Vector3 forward;
		static Vector3 right;
		static Vector3 up;

		union {
			struct {
				float x;
				float y;
				float z;
			};
			struct {
				float coords[3];
			};
		};		

		Vector3() = default;
		Vector3(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
		}
		Vector3(const Vector2& xy, float _z) {
			x = xy.x;
			y = xy.y;
			z = _z;
		}
		Vector3(const Matrix44& matrix);

		Vector3 cross(const Vector3& other) const;

		inline float dot(const Vector3& other) const {
			return x * other.x + y * other.y + z * other.z;
		}

		inline Vector3 operator * (float f) const {
			return Vector3(x * f, y * f, z * f);
		}

		inline Vector3 operator * (const Vector3& other) const {
			return Vector3(x * other.x, y * other.y, z * other.z);
		}

		inline Vector3 operator + (const Vector3& other) const {
			return Vector3(x + other.x, y + other.y, z + other.z);
		}

		inline Vector3 operator - (const Vector3& other) const {
			return Vector3(x - other.x, y - other.y, z - other.z);
		}

		inline Vector3 operator / (float f) const {
			return this->operator*(1.f / f);
		}

		inline Vector3 operator -() const {
			return this->operator*(-1.f);
		}

		inline Vector3 reflect(const Vector3& normal) const {
			return this->operator-(normal * 2.f * this->dot(normal));
		}

		float length() const;
		Vector3& normalize();
		Vector3 normalized() const;
	};
}
