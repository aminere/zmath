
#include "pch.h"
#include "plane.h"

namespace zmath {
	Plane Plane::fromNormal(const Vector3& normal, float distFromOrigin) {
		return { normal, distFromOrigin };
	}

	Plane Plane::fromNormal(const Vector3& normal, const Vector3& point) {
		return { normal, point.dot(normal) };
	}

	Plane Plane::fromPoints(const Vector3& v1, const Vector3& v2, const Vector3& v3) {
		auto normal = (v3 - v1).cross(v2 - v1).normalize();
		return fromNormal(normal, v1);
	}

	Plane::Classification Plane::classify(const Vector3& point) const {
		auto nominator = normal.dot(point) - distFromOrigin;
		if (nominator > 0.000001f) {
			return Classification::Front;
		} else if (nominator < -0.000001f) {
			return Classification::Back;
		} else {
			return Classification::Planar;
		}
	}
}

