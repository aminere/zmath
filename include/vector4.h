#pragma once

namespace zmath {

	class Vector4 {
	public:

		static Vector4 zero;
		static Vector4 one;

		union {
			struct {
				float x;
				float y;
				float z;
				float w;
			};

			struct {
				Vector3 xyz;
				float w2;
			};

			struct {
				float coords[4];
			};
		};

		Vector4() = default;
		Vector4(float _x, float _y, float _z, float _w) {
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}
		Vector4(const Vector3& _xyz, float _w) {
			xyz = _xyz;
			w = _w;
		}

		inline void operator = (const Vector3& v) {
			xyz = v;
		}

		inline Vector4 operator * (float f) const {
			return Vector4(x * f, y * f, z * f, w * f);
		}

		inline Vector4 operator * (const Vector4& other) const {
			return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
		}

		inline Vector4 operator / (float f) const {
			return this->operator*(1.f / f);
		}

	};
}

