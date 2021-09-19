
#include "pch.h"
#include "clipping.h"
#include "ray.h"
#include "collision.h"

#include <assert.h>

namespace zmath {

	Clipping::Status Clipping::trianglePlane(const Triangle& triangle, const Plane& plane, std::vector<ClippedTriangle>& out) {

		struct Edge {
			int vertices[2];
			Vector3 intersection;
			float mixFactor;
		};

		std::vector<int> front;
		std::vector<int> back;
		bool inside[3] = { false, false, false };
		for (int i = 0; i < 3; ++i) {
			auto point = triangle.points[i];
			auto c = plane.classify(point);
			inside[i] = c == Plane::Classification::Front;
			if (inside[i]) {
				front.push_back(i);
			} else {
				back.push_back(i);
			}
		}

		if (front.size() == 0) {
			return Status::Hidden;
		}

		if (back.size() == 0) {			
			return Status::Visible;
		}

		Edge edges[3] = {
			{ {0, 1}, Vector3::zero, .0f },
			{ {1, 2}, Vector3::zero, .0f },
			{ {2, 0}, Vector3::zero, .0f },
		};

		// Determine clipped edges, and their intersection with the clipping plane
		for (int i = 0; i < 3; ++i) {
			auto inside1 = inside[edges[i].vertices[0]];
			auto inside2 = inside[edges[i].vertices[1]];
			if (inside1 != inside2) {
				auto p1i = inside1 ? edges[i].vertices[0] : edges[i].vertices[1];
				auto p2i = inside1 ? edges[i].vertices[1] : edges[i].vertices[0];
				auto p1 = triangle.points[p1i];
				auto p2 = triangle.points[p2i];
				Ray ray(p1, (p2 - p1).normalize());
				Collision::RayPlaneResult result;
				auto c1 = Collision::rayPlane(ray, plane, result);
				assert(c1);
				edges[i].intersection = result.intersection;
				auto mixFactor = (result.intersection - p1).length() / (p2 - p1).length();
				edges[i].mixFactor = inside1 ? mixFactor : (1.f - mixFactor);
			}
		}

		auto getClippedEdgeVertices = [&](int edgeIndex) -> std::vector<ClippedVertex> {
			auto inside1 = inside[edges[edgeIndex].vertices[0]];
			auto inside2 = inside[edges[edgeIndex].vertices[1]];
			assert(inside1 != inside2);
			if (inside1) {
				return {
					{ edges[edgeIndex].vertices[0], Vector3::zero, 0.f, -1, -1 },
					{ -1, edges[edgeIndex].intersection, edges[edgeIndex].mixFactor, edges[edgeIndex].vertices[0], edges[edgeIndex].vertices[1] }
				};

			} else {
				return {
					{ -1, edges[edgeIndex].intersection, edges[edgeIndex].mixFactor, edges[edgeIndex].vertices[0], edges[edgeIndex].vertices[1] },
					{ edges[edgeIndex].vertices[1], Vector3::zero, 0.f, -1, -1 },
				};
			}
		};

		if (front.size() == 1) {

			// Output 1 triangle
			std::vector<ClippedVertex> vertices;
			for (int i = 0; i < 3; ++i) {
				auto inside1 = inside[edges[i].vertices[0]];
				auto inside2 = inside[edges[i].vertices[1]];
				if (inside1 != inside2) {
					vertices.push_back(getClippedEdgeVertices(i)[0]);
				} else {
					assert(!inside1);
					assert(!inside2);
					auto previousEdge = i == 0 ? 2 : i - 1;
					vertices.push_back(getClippedEdgeVertices(previousEdge)[1]);
				}
			}

			out.push_back({ vertices });
			return Status::Clipped;

		} else {

			// Output 2 triangles
			auto inside1 = inside[edges[0].vertices[0]];
			auto inside2 = inside[edges[0].vertices[1]];
			if (inside1 == inside2) {
				assert(inside1);
				assert(inside2);

				ClippedTriangle triangle1{ {
					{ edges[0].vertices[0], Vector3::zero, 0.f, 0, 0 },
					{ edges[0].vertices[1], Vector3::zero, 0.f, 0, 0 },
					{ -1, edges[1].intersection, edges[1].mixFactor, edges[1].vertices[0], edges[1].vertices[1] }
				}};

				ClippedTriangle triangle2{ {
					{ edges[0].vertices[0], Vector3::zero, 0.f, 0, 0 },
					{ -1, edges[1].intersection, edges[1].mixFactor, edges[1].vertices[0], edges[1].vertices[1] },
					{ -1, edges[2].intersection, edges[2].mixFactor, edges[2].vertices[0], edges[2].vertices[1] }
				} };

				out = { triangle1, triangle2 };

			} else if (inside1) {

				ClippedTriangle triangle1{ {
					{ edges[0].vertices[0], Vector3::zero, 0.f, 0, 0 },
					{ -1, edges[0].intersection, edges[0].mixFactor, edges[0].vertices[0], edges[0].vertices[1] },
					{ -1, edges[1].intersection, edges[1].mixFactor, edges[1].vertices[0], edges[1].vertices[1] }
				} };

				ClippedTriangle triangle2{ {
					{ edges[0].vertices[0], Vector3::zero, 0.f, 0, 0 },
					{ -1, edges[1].intersection, edges[1].mixFactor, edges[1].vertices[0], edges[1].vertices[1] },
					{ edges[1].vertices[1], Vector3::zero, 0.f, 0, 0 }
				} };

				out = { triangle1, triangle2 };

			} else {

				ClippedTriangle triangle1{ {
					{ -1, edges[0].intersection, edges[0].mixFactor, edges[0].vertices[0], edges[0].vertices[1] },
					{ edges[1].vertices[0], Vector3::zero, 0.f, 0, 0 },
					{ edges[1].vertices[1], Vector3::zero, 0.f, 0, 0 },
				} };

				ClippedTriangle triangle2{ {
					{ -1, edges[0].intersection, edges[0].mixFactor, edges[0].vertices[0], edges[0].vertices[1] },
					{ edges[1].vertices[1], Vector3::zero, 0.f, 0, 0 },
					{ -1, edges[2].intersection, edges[2].mixFactor, edges[2].vertices[0], edges[2].vertices[1] },
				} };

				out = { triangle1, triangle2 };
			}

			return Status::Clipped;
		}		
	}	
}

