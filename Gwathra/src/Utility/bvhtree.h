#pragma once
#include <gwm.h>
#include <stdint.h>
#include <vector>
#include <numeric>

namespace gwa {
	enum GeometryType {
		TRIANGLE, QUAD, SPHERE, BOX
	};

	struct BVHNode {
		BVHNode() = default;

		BVHNode(gwm::Vec3 boundMin, gwm::Vec3 boundMax, gwm::Vec3 centroid, uint32_t primCount, uint32_t primStart)
			: boundMin(boundMin), boundMax(boundMax), centroid(centroid), primCount(primCount), primStart(primStart), leftChild(0), rightChild(0) {
		};

		gwm::Vec3 boundMin, boundMax;
		gwm::Vec3 centroid;
		uint32_t leftChild, rightChild;
		uint32_t primStart, primCount;
	};

	class BVHTree {
		public:

			BVHTree() {

			}

			BVHTree(std::vector<float>& pVerticies, std::vector<uint32_t>& pIds) : m_vertices(pVerticies), m_ids(pIds) {
				nodes = std::vector<BVHNode>();

			}

			BVHTree(std::vector<float>& pVerticies, std::vector<uint32_t>& pIds, std::vector<BVHNode>& nodes) : m_vertices(pVerticies), m_ids(pIds), nodes(nodes) {

			}

			bool buildBVHTree();
			
			std::vector<BVHNode> nodes;
			
			
		private:
			std::vector<uint32_t> m_ids;
			std::vector<float> m_vertices;


			void findBBox(BVHNode& node);

			void splitTreeLongestAxis(BVHNode& node);
			
	};
}
