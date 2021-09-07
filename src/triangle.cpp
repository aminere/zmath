
#include "pch.h"
#include "triangle.h"

namespace zmath {

	bool Triangle::contains(const Vector3& p, Vector3& coords) const {
		if (getBarycentricCoords(p, coords)) {
			if (coords.y < 0) {
				return false;
			}
			if (coords.z < 0) {
				return false;
			}
			if (coords.y + coords.z > 1.f) {
				return false;
			}
			return true;
		} else {
			return false;
		}
	}

	bool Triangle::getBarycentricCoords(const Vector3& p, Vector3& out) const {
		auto v0 = b - a;
		auto v1 = c - a;
		auto v2 = p - a;
		auto d00 = v0.dot(v0);
		auto d01 = v0.dot(v1);
		auto d11 = v1.dot(v1);
		auto d20 = v2.dot(v0);
		auto d21 = v2.dot(v1);
		auto det = (d00 * d11 - d01 * d01);
		if (det != 0.f) {
			auto v = (d11 * d20 - d01 * d21) / det;
			auto w = (d00 * d21 - d01 * d20) / det;
			auto u = 1.0f - v - w;
			out = Vector3::create(u, v, w);
			return true;
		}
		return false;
	}
}

