#pragma once
#include <gwm.h>
namespace gwa {
	enum GeometryType {
		TRIANGLE, QUAD, SPHERE, BOX
	};

	struct BVHNode {
		gwm::Vec3 boundMin, boundMax;
		gwm::Vec3 center;
		uint32_t leftChild, rightChild;
		uint32_t primStart, primCount;

		BVHNode( gwm::Vec3 boundMin, gwm::Vec3 boundMax, gwm::Vec3 center, uint32_t leftChild, uint32_t rightChild, uint32_t primCount, uint32_t primtStart)
			: boundMin(boundMin), boundMax(boundMax), center(center), leftChild(leftChild), rightChild(rightChild), primCount(primCount), primStart(primStart) {

		};
	};

	class BVHTree {
		public:
			std::vector<BVHNode> nodes;
			std::vector<float> vertices;
		private:

	};
}
