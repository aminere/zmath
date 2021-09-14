
#include "pch.h"
#include "quaternion.h"
#include "matrix44.h"
#include <cmath>

namespace zmath {

	Quaternion Quaternion::identity = { 0, 0, 0, 1 };

	Quaternion::Quaternion(const Vector3& eulerAngles, RotationOrder order) {
		// based on Threejs
		const auto c1 = (float)cos(x / 2.f);
		const auto c2 = (float)cos(y / 2.f);
		const auto c3 = (float)cos(z / 2.f);
		const auto s1 = (float)sin(x / 2.f);
		const auto s2 = (float)sin(y / 2.f);
		const auto s3 = (float)sin(z / 2.f);
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

	Quaternion::Quaternion(const zmath::Matrix44& matrix) {
		// based on Threejs
		auto te = matrix.data;
		auto m11 = te[0], m12 = te[4], m13 = te[8],
			m21 = te[1], m22 = te[5], m23 = te[9],
			m31 = te[2], m32 = te[6], m33 = te[10],
			trace = m11 + m22 + m33;

		if (trace > 0.f) {
			auto s = 0.5f / sqrt(trace + 1.0f);
			w = 0.25f / s;
			x = (m32 - m23) * s;
			y = (m13 - m31) * s;
			z = (m21 - m12) * s;

		} else if (m11 > m22 && m11 > m33) {
			auto s = 2.0f * sqrt(1.0f + m11 - m22 - m33);
			w = (m32 - m23) / s;
			x = 0.25f * s;
			y = (m12 + m21) / s;
			z = (m13 + m31) / s;

		} else if (m22 > m33) {
			auto s = 2.0f * sqrt(1.0f + m22 - m11 - m33);
			w = (m13 - m31) / s;
			x = (m12 + m21) / s;
			y = 0.25f * s;
			z = (m23 + m32) / s;

		} else {
			auto s = 2.0f * sqrt(1.0f + m33 - m11 - m22);
			w = (m21 - m12) / s;
			x = (m13 + m31) / s;
			y = (m23 + m32) / s;
			z = 0.25f * s;
		}
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
}
