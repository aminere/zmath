
#include "pch.h"
#include "quaternion.h"
#include <cmath>

namespace zmath {

	Quaternion Quaternion::identity = { 0, 0, 0, 1 };

	Quaternion Quaternion::fromEulerAngles(float x, float y, float z, RotationOrder order) {
		// based on Threejs
		const auto c1 = (float)cos(x / 2.f);
		const auto c2 = (float)cos(y / 2.f);
		const auto c3 = (float)cos(z / 2.f);
		const auto s1 = (float)sin(x / 2.f);
		const auto s2 = (float)sin(y / 2.f);
		const auto s3 = (float)sin(z / 2.f);
		Quaternion q;
		if (order == RotationOrder::YXZ) {
			q.x = s1 * c2 * c3 + c1 * s2 * s3;
			q.y = c1 * s2 * c3 - s1 * c2 * s3;
			q.z = c1 * c2 * s3 - s1 * s2 * c3;
			q.w = c1 * c2 * c3 + s1 * s2 * s3;
		} else if (order == RotationOrder::ZYX) {
			q.x = s1 * c2 * c3 - c1 * s2 * s3;
			q.y = c1 * s2 * c3 + s1 * c2 * s3;
			q.z = c1 * c2 * s3 - s1 * s2 * c3;
			q.w = c1 * c2 * c3 + s1 * s2 * s3;
		} else if (order == RotationOrder::XYZ) {
			q.x = s1 * c2 * c3 + c1 * s2 * s3;
			q.y = c1 * s2 * c3 - s1 * c2 * s3;
			q.z = c1 * c2 * s3 + s1 * s2 * c3;
			q.w = c1 * c2 * c3 - s1 * s2 * s3;
		} else if (order == RotationOrder::ZXY) {
			q.x = s1 * c2 * c3 - c1 * s2 * s3;
			q.y = c1 * s2 * c3 + s1 * c2 * s3;
			q.z = c1 * c2 * s3 + s1 * s2 * c3;
			q.w = c1 * c2 * c3 - s1 * s2 * s3;
		} else if (order == RotationOrder::YZX) {
			q.x = s1 * c2 * c3 + c1 * s2 * s3;
			q.y = c1 * s2 * c3 + s1 * c2 * s3;
			q.z = c1 * c2 * s3 - s1 * s2 * c3;
			q.w = c1 * c2 * c3 - s1 * s2 * s3;
		} else if (order == RotationOrder::XZY) {
			q.x = s1 * c2 * c3 - c1 * s2 * s3;
			q.y = c1 * s2 * c3 - s1 * c2 * s3;
			q.z = c1 * c2 * s3 + s1 * s2 * c3;
			q.w = c1 * c2 * c3 + s1 * s2 * s3;
		}
		return q.normalize();
	}

	Quaternion& Quaternion::normalize() {
		auto l = length();
		if (l == 0.f) {
			//if (process.env.NODE_ENV == = "development") {
			//    console.assert(false, "Normalizing a zero Quaternion");
			//}
		} else {
			l = 1.f / l;
			x *= l;
			y *= l;
			z *= l;
			w *= l;
		}
		return *this;
	}

	float Quaternion::length() const {
		return (float)sqrt((float)((x * x) + (y * y) + (z * z) + (w * w)));
	}

	Vector3 Quaternion::operator * (const Vector3& v) const {
		// calculate quat * vector
		const auto ix = w * v.x + y * v.z - z * v.y;
		const auto iy = w * v.y + z * v.x - x * v.z;
		const auto iz = w * v.z + x * v.y - y * v.x;
		const auto iw = -x * v.x - y * v.y - z * v.z;

		// calculate result * inverse quat
		return Vector3::create(
			ix * w + iw * -x + iy * -z - iz * -y,
			iy * w + iw * -y + iz * -x - ix * -z,
			iz * w + iw * -z + ix * -y - iy * -x
		);
	}
}
