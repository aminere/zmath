
#include "pch.h"
#include "quaternion.h"
#include "matrix44.h"
#include <cmath>

namespace zmath {

	Quaternion Quaternion::identity = { 0, 0, 0, 1 };

	Quaternion::Quaternion(const Vector3& eulerAngles, RotationOrder order) {
		// based on Threejs
		const auto c1 = (float)cos(eulerAngles.x / 2.f);
		const auto c2 = (float)cos(eulerAngles.y / 2.f);
		const auto c3 = (float)cos(eulerAngles.z / 2.f);
		const auto s1 = (float)sin(eulerAngles.x / 2.f);
		const auto s2 = (float)sin(eulerAngles.y / 2.f);
		const auto s3 = (float)sin(eulerAngles.z / 2.f);
		if (order == RotationOrder::YXZ) {
			x = s1 * c2 * c3 + c1 * s2 * s3;
			y = c1 * s2 * c3 - s1 * c2 * s3;
			z = c1 * c2 * s3 - s1 * s2 * c3;
			w = c1 * c2 * c3 + s1 * s2 * s3;
		} else if (order == RotationOrder::ZYX) {
			x = s1 * c2 * c3 - c1 * s2 * s3;
			y = c1 * s2 * c3 + s1 * c2 * s3;
			z = c1 * c2 * s3 - s1 * s2 * c3;
			w = c1 * c2 * c3 + s1 * s2 * s3;
		} else if (order == RotationOrder::XYZ) {
			x = s1 * c2 * c3 + c1 * s2 * s3;
			y = c1 * s2 * c3 - s1 * c2 * s3;
			z = c1 * c2 * s3 + s1 * s2 * c3;
			w = c1 * c2 * c3 - s1 * s2 * s3;
		} else if (order == RotationOrder::ZXY) {
			x = s1 * c2 * c3 - c1 * s2 * s3;
			y = c1 * s2 * c3 + s1 * c2 * s3;
			z = c1 * c2 * s3 + s1 * s2 * c3;
			w = c1 * c2 * c3 - s1 * s2 * s3;
		} else if (order == RotationOrder::YZX) {
			x = s1 * c2 * c3 + c1 * s2 * s3;
			y = c1 * s2 * c3 + s1 * c2 * s3;
			z = c1 * c2 * s3 - s1 * s2 * c3;
			w = c1 * c2 * c3 - s1 * s2 * s3;
		} else if (order == RotationOrder::XZY) {
			x = s1 * c2 * c3 - c1 * s2 * s3;
			y = c1 * s2 * c3 - s1 * c2 * s3;
			z = c1 * c2 * s3 + s1 * s2 * c3;
			w = c1 * c2 * c3 + s1 * s2 * s3;
		}
		normalize();
	}

	Quaternion::Quaternion(const Vector3& axis, float radians) {
		auto halfAngle = radians / 2.f, s = sin(halfAngle);
		x = axis.x * s;
		y = axis.y * s;
		z = axis.z * s;
		w = cos(halfAngle);
		normalize();
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
		return Vector3(
			ix * w + iw * -x + iy * -z - iz * -y,
			iy * w + iw * -y + iz * -x - ix * -z,
			iz * w + iw * -z + ix * -y - iy * -x
		);
	}

	Quaternion Quaternion::operator*(const Quaternion& q) const {
		// based on Threejs
		float qax = q.x, qay = q.y, qaz = q.z, qaw = q.w;
		float qbx = x, qby = y, qbz = z, qbw = w;
		Quaternion out;
		out.x = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
		out.y = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
		out.z = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
		out.w = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;
		return out;
	}
}
