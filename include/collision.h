#pragma once

#include "ray.h"
#include "plane.h"

namespace zmath {
	class Collision {
	public:

		struct RayPlaneResult {
			Vector3 intersection;
			Plane::Classification classification;
		};

		static bool rayPlane(const Ray& ray, const Plane& plane, RayPlaneResult& out);
	};
}

