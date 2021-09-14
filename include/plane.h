#pragma once

namespace zmath {
	class Plane {
	public:

		Vector3 normal = Vector3::up;
		float distFromOrigin = 0.f;

		enum class Classification {
			Front,
			Back,
			Planar
		};

		Plane() = default;
		Plane(const Vector3& normal, float distFromOrigin);
		Plane(const Vector3& normal, const Vector3& point);
		Plane(const Vector3& v1, const Vector3& v2, const Vector3& v3);

		Classification classify(const Vector3& point) const;
	};
}
