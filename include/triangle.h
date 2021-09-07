#pragma once

#include "vector3.h"

namespace zmath {
	class Triangle {
	public:

		Vector3 a;
		Vector3 b;
		Vector3 c;

		Triangle() = default;
		Triangle(const Vector3& _a, const Vector3& _b, const Vector3& _c)
			: a(_a)
			, b(_b)
			, c(_c) {

		}

		bool contains(const Vector3& p, Vector3& coords) const;
		bool getBarycentricCoords(const Vector3& p, Vector3& out) const;
	};
}

