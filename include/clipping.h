#pragma once

#include "triangle.h"
#include "plane.h"

#include <vector>

namespace zmath {
	class Clipping {
	public:

		enum class Status {
			Visible,
			Hidden,
			Clipped
		};

		struct ClippedVertex {
			int index;
			Vector3 clippedPosition;
			float mixFactor;
			int mixVertex1;
			int mixVertex2;
		};

		struct ClippedTriangle {
			std::vector<ClippedVertex> vertices;
		};

		static Status trianglePlane(const Triangle& triangle, const Plane& plane, std::vector<ClippedTriangle>& out);
	};
}

