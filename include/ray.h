#pragma once

namespace zmath {
	class Ray {
	public:

		Vector3 origin;
		Vector3 direction;
		
		Ray(const Vector3& origin, const Vector3& direction);
	};
}
