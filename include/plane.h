#pragma once

#include "vector3.h"

namespace zmath {
	class Plane {
	public:

		Vector3 normal = Vector3::up;
		float distFromOrigin = 0.f;

		enum class Classification {
			Front,
			Back,
			Planar
		};

		static Plane fromNormal(const Vector3& normal, float distFromOrigin);
		static Plane fromNormal(const Vector3& normal, const Vector3& point);
		static Plane fromPoints(const Vector3& v1, const Vector3& v2, const Vector3& v3);

		Classification classify(const Vector3& point) const;
	};
}
