
#include "pch.h"
#include "clipping.h"
#include "ray.h"
#include "collision.h"

#include <assert.h>

namespace zmath {
	bool Clipping::trianglePlane(const Triangle& triangle, const Plane& plane, std::vector<Triangle>& out) {

		std::vector<Vector3> front;
		std::vector<Vector3> back;

		for (int i = 0; i < 3; ++i) {
			auto point = triangle.points[i];
			auto c = plane.classify(point);
			if (c == Plane::Classification::Front) {
				front.push_back(point);
			} else {
				back.push_back(point);
			}
		}

		if (back.size() == 3) {
			return false;
		}

		if (front.size() == 3) {
			out.push_back(triangle);
			return true;
		}

		auto normal = (triangle.b - triangle.a).cross(triangle.c - triangle.a);
		auto fixNormalIfNecessary = [&](const Triangle& newTriangle) {
			auto newNormal = (newTriangle.b - newTriangle.a).cross(newTriangle.c - newTriangle.a);
			if (normal.dot(newNormal) < 0.f) {
				return Triangle(
					newTriangle.a,
					newTriangle.c,
					newTriangle.b
				);
			} else {
				return newTriangle;
			}
		};

		if (back.size() == 2) {
			assert(front.size() == 1);

			Ray r1(front[0], (back[0] - front[0]).normalize());
			Collision::RayPlaneResult result1;
			auto c1 = Collision::rayPlane(r1, plane, result1);
			assert(c1);

			Ray r2(front[0], (back[1] - front[0]).normalize());
			Collision::RayPlaneResult result2;
			auto c2 = Collision::rayPlane(r2, plane, result2);
			assert(c2);
			
			out.push_back(fixNormalIfNecessary(Triangle(front[0], result1.intersection, result2.intersection)));

		} else {
			assert(front.size() == 2);
			assert(back.size() == 1);

			Ray r1(front[0], (back[0] - front[0]).normalize());
			Collision::RayPlaneResult result1;
			auto c1 = Collision::rayPlane(r1, plane, result1);
			assert(c1);

			Ray r2(front[1], (back[0] - front[1]).normalize());
			Collision::RayPlaneResult result2;
			auto c2 = Collision::rayPlane(r2, plane, result2);
			assert(c2);

			out.push_back(fixNormalIfNecessary(Triangle(front[0], result1.intersection, result2.intersection)));
			out.push_back(fixNormalIfNecessary(Triangle(front[0], result2.intersection, front[1])));
		}

		return true;
	}
}

