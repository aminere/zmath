#pragma once

#include "triangle.h"
#include "plane.h"

#include <vector>

namespace zmath {
	class Clipping {
	public:		

		static bool trianglePlane(const Triangle& triangle, const Plane& plane, std::vector<Triangle>& out);
	};
}
