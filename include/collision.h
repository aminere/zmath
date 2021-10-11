#pragma once

#include "ray.h"
#include "plane.h"
#include "triangle.h"

namespace zmath {
	class Collision {
	public:

		struct RayPlaneResult {
			Vector3 intersection;
			Plane::Classification classification;
		};

		struct RayTriangleResult : public RayPlaneResult {};

		static bool rayPlane(const Ray& ray, const Plane& plane, RayPlaneResult& out);
		static bool rayTriangle(const Ray& ray, const Triangle& triangle, RayTriangleResult& out);
	};
}

