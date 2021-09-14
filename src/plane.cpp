
#include "pch.h"
#include "plane.h"

namespace zmath {
	Plane::Plane(const Vector3& _normal, float _distFromOrigin)
		: normal(_normal)
		, distFromOrigin(_distFromOrigin) {
	}

	Plane::Plane(const Vector3& _normal, const Vector3& point)
		: normal(_normal)
		, distFromOrigin(point.dot(_normal)) {
	}

	Plane::Plane(const Vector3& v1, const Vector3& v2, const Vector3& v3)
		: Plane((v3 - v1).cross(v1 - v2).normalize(), v1) {
	}

	Plane::Classification Plane::classify(const Vector3& point) const {
		auto nominator = normal.dot(point) - distFromOrigin;
		if (nominator > epsilon) {
			return Classification::Front;
		} else if (nominator < -epsilon) {
			return Classification::Back;
		} else {
			return Classification::Planar;
		}
	}
}

