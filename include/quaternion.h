#pragma once

namespace zmath {

	class Quaternion {
	public:

		enum RotationOrder {
			YXZ,
			ZYX,
			XYZ,
			ZXY,
			YZX,
			XZY
		};

		static Quaternion identity;
		static Quaternion fromEulerAngles(float x, float y, float z, RotationOrder order = RotationOrder::YXZ);

		float x = 0.f;
		float y = 0.f;
		float z = 0.f;
		float w = 1.f;

		Quaternion() = default;
		Quaternion(float _x, float _y, float _z, float _w) {
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}

		Quaternion& normalize();

		float length() const;

		Vector3 operator * (const Vector3& v) const;
	};
}
