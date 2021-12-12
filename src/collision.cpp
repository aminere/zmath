
#include "pch.h"
#include "collision.h"

namespace zmath {
	bool Collision::rayPlane(const Ray& ray, const Plane& plane, RayPlaneResult& out) {
        auto nominator = plane.normal.dot(ray.origin) - plane.distFromOrigin;
        if (isZero(nominator)) {
            out.intersection = ray.origin;
            out.classification = Plane::Classification::Planar;
        } else {
            auto denominator = plane.normal.dot(ray.direction);
            if (isZero(denominator)) {
                // ray is parallel to the plane, no intersection
                return false;
            } else {
                auto toIntersection = -nominator / denominator;
                if (toIntersection < 0.f) {
                    // intersection is behind the ray origin
                    return false;
                } else {
                    out.intersection = ray.origin + ray.direction * toIntersection;
                }
            }
            out.classification = nominator > 0.f ? Plane::Classification::Front : Plane::Classification::Back;
        }
        return true;
	}

    bool Collision::rayTriangle(const Ray& ray, const Triangle& triangle, RayTriangleResult& out) {
        Plane plane(triangle.a, triangle.b, triangle.c);
        if (!rayPlane(ray, plane, out)) {
            return false;
        }

        if (!triangle.contains(out.intersection)) {
            return false;
        }

        return true;
    }
}

