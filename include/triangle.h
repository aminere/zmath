#pragma once

namespace zmath {
	class Triangle {
	public:

		union {
			struct {
				Vector3 a;
				Vector3 b;
				Vector3 c;
			};
			struct {
				Vector3 points[3];
			};
		};
		

		Triangle() = default;
		Triangle(const Vector3& _a, const Vector3& _b, const Vector3& _c)
			: a(_a)
			, b(_b)
			, c(_c) {

		}

		bool contains(const Vector3& p) const;
		bool containsCoords(const Vector3& barycentricCoords) const;
		bool getBarycentricCoords(const Vector3& p, Vector3& out) const;		
	};
}

