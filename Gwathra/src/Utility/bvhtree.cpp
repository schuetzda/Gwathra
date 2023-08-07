#include "bvhtree.h"
#include <iostream>
namespace gwa {

	bool BVHTree::buildBVHTree()
	{
		if (m_vertices.empty() || m_ids.empty()) {
			std::cerr << "Vertices or Ids missing.";
			return false;
		}
		BVHNode root;
		root.primStart = 0;
		root.primCount = m_ids.size();
		root.boundMax = root.boundMin = gwm::Vec3(m_vertices[root.primStart * 3], m_vertices[root.primStart * 3 + 1], m_vertices[root.primStart * 3 + 2]);
		findBBox(root);
		splitTreeLongestAxis(root);
	}

	void BVHTree::findBBox(BVHNode& node) {
		for (int i = node.primStart + 1; i < node.primCount; ++i) {

			node.boundMin[0] = std::fmin(m_vertices[m_ids[i]*3], node.boundMin[0]);
			node.boundMin[1] = std::fmin(m_vertices[m_ids[i]*3+1], node.boundMin[1]);
			node.boundMin[2] = std::fmin(m_vertices[m_ids[i]*3+2], node.boundMin[2]);

			node.boundMax[0] = std::fmax(m_vertices[m_ids[i]*3], node.boundMax[0]);
			node.boundMax[1] = std::fmax(m_vertices[m_ids[i]*3+1], node.boundMax[1]);
			node.boundMax[2] = std::fmax(m_vertices[m_ids[i]*3+2], node.boundMax[2]);
		}
		node.centroid = 0.5f * (node.boundMin + node.boundMax);
	}

	void BVHTree::splitTreeLongestAxis(BVHNode& node) {
		gwm::Vec3 extent = node.boundMax - node.boundMin;

		uint32_t axis = 0;
		if (extent[1] > extent[0]) axis = 1;
		if (extent[2] > extent[axis]) axis = 2;
		float splitPos = node.boundMin[axis] + extent[axis] * 0.5f;
		uint32_t nodesEnd = node.primStart + node.primCount-1;
		for (uint32_t i = node.primStart; i <= nodesEnd; ++i) {
			if (nodes[m_ids[i]].centroid[axis] > splitPos) {
				std::swap(m_ids[i], m_ids[nodesEnd]);
				nodesEnd--;
			}
		}
	}
}
