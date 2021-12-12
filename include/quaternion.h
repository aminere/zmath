#pragma once

#include "vector3.h"

namespace zmath {

	class Quaternion {
	public:

		enum class RotationOrder {
			YXZ,
			ZYX,
			XYZ,
			ZXY,
			YZX,
			XZY
		};

		static Quaternion identity;

		float x = 0.f;
		float y = 0.f;
		float z = 0.f;
		float w = 1.f;

		Quaternion() = default;
		Quaternion(float _x, float _y, float _z, float _w)
		: x(_x)
		, y(_y)
		, z(_z)
		, w(_w) {			
		}

		Quaternion(const Vector3& eulerAngles, RotationOrder order = RotationOrder::YXZ);
		Quaternion(const Vector3& axis, float angle);

		Quaternion& normalize();

		float length() const;

		Vector3 operator * (const Vector3& v) const;
		Quaternion operator * (const Quaternion& q) const;
	};
}
