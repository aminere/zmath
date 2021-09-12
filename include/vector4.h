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
	};
}

