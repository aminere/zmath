
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

		if (back.size() == 2) {
			assert(front.size() == 1);

			Ray r1(back[0], (front[0] - back[0]).normalize());
			Collision::RayPlaneResult result1;
			auto c1 = Collision::rayPlane(r1, plane, result1);
			assert(c1);

			Ray r2(back[1], (front[0] - back[1]).normalize());
			Collision::RayPlaneResult result2;
			auto c2 = Collision::rayPlane(r2, plane, result2);
			assert(c2);

			out.push_back(Triangle(result1.intersection, front[0], result2.intersection));

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

			out.push_back(Triangle(front[0], result1.intersection, result2.intersection));
			out.push_back(Triangle(front[0], result2.intersection, front[1]));
		}

		return true;
	}
}

